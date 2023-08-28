#include "timer.hpp"
#include "agc.hpp"
#include <functional>
#include <thread>
#include <sockpp/socket.h>

namespace agcplusplus::block2 {

void Timer::start() {
    // Start a thread where we can look for incoming connections
    std::thread socket_thread(&Timer::accept_dsky_connections, *this);

    // Start ticking our various functions at their given intervals
    while (true) {
        // Calculate the time that we should tick the clock next, before any code executes
        auto started_at = std::chrono::steady_clock::now();
        auto x = started_at + std::chrono::milliseconds(1); // We can complete 1024 timepulses in 1 millisecond

        for (word t = 0; t < TIMEPULSES_PER_MILLISECOND; ++t) {
            ++total_ticks;

            // Perform CPU timepulse every tick
            Agc::cpu.tick();

            // Copy the CPU's IIP signal to the scaler for RUPT lock checking
            Agc::scaler.update_interrupt_state(Agc::cpu.iip);

            // If the CPU is executing a TC instruction at any time, tell the scaler
            bool check_notbuggy = (Agc::cpu.current_subinstruction.name == "TC0" || Agc::cpu.current_subinstruction.name == "TCF0");
            if (check_notbuggy) {
                Agc::scaler.signal_tc_started();
            } else if (Agc::cpu.current_timepulse == 4 && !Agc::cpu.inkl) {
                // If it's timepulse 4 and the CPU is not processing a counter or executing TC/TCF, tell the scaler
                Agc::scaler.signal_tc_ended();
            }

            // Tick the scaler every 10 ticks (every 10 milliseconds)
            if ((total_ticks % 10) == 0) {
                Agc::scaler.tick();
            }

            // Other ticks go here
        }

        auto ended_at = std::chrono::steady_clock::now();

        //auto batch_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(ended_at - started_at);
        //std::cout << "Batched ticks took " << (batch_duration.count() / 1000000.0) << " milliseconds." << std::endl;

        // Wait the remaining amount of time before ticking the clock again
        std::this_thread::sleep_until(x);
    }
}

void Timer::accept_dsky_connections() {
    while (true) {
        // Set up the socket to connect to the DSKY server
        sockpp::socket_initializer::initialize();
        in_port_t port = 19697;
        sockpp::tcp_acceptor dsky_conn(port);

        // Update the DSKY client connection
        sockpp::inet_address peer;
        sockpp::tcp_socket sock = dsky_conn.accept(&peer);
        std::cout << "DSKY connection from " << peer << std::endl;

        if (!sock) {
            std::cerr << "Error accepting connection!" << std::endl;
        } else {
            std::thread dsky_thread(&Timer::process_dsky, *this, std::move(sock));
            dsky_thread.detach();
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Timer::process_dsky(sockpp::tcp_socket sock) {
    try {
        sock.set_non_blocking(true);
        while (true) {
            // Calculate the time that we should process the DSKY next, before any code executes
            auto started_at = std::chrono::steady_clock::now();
            auto x = started_at + std::chrono::milliseconds(1);

            if (sock.is_open()) {

                // Read from the DSKY first to check its state
                char read_buf[4];
                size_t result = sock.read(read_buf, 4);
                if (result == 0) {
                    std::cout << "DSKY connection closed" << std::endl;
                    sock.close();
                    break;
                } else if (result == 4) {
                    // Read the packet, form of:
                    // 00utpppp 01pppddd 10dddddd 11dddddd
                    // where p are I/O channel bits, d are data bits,
                    // u is the bitmask flag, and t is the counter request flag.

                    // First, verify the signature of the packet by checking
                    // the 2 most significant bits in each byte.
                    uint8_t signature = 0;
                    signature |= read_buf[0] & 0b11000000;
                    signature |= (read_buf[1] & 0b11000000) >> 2;
                    signature |= (read_buf[2] & 0b11000000) >> 4;
                    signature |= (read_buf[3] & 0b11000000) >> 6;
                    if (signature == 0b00011011) {  // should be 00 01 10 11
                        // If the signature is valid, parse the data
                        bool bitmask = ((read_buf[0] & 0b00100000) != 0);
                        bool unprogrammed_sequence = ((read_buf[0] & 0b00010000) != 0);
                        uint8_t channel = ((read_buf[0] & 0b00001111) << 3) |
                                          ((read_buf[1] & 0b00111000) >> 3);
                        uint16_t data = ((read_buf[1] & 0b00000111) << 11) |
                                        ((read_buf[2] & 0b00111111) << 5) |
                                        (read_buf[3] & 0b00111111);
                        /*
                        std::cout << "DSKY read success (result = " << result << "), packet data is:" << std::endl;
                        std::oct(std::cout);
                        std::cout << " u = " << bitmask;
                        std::cout << " t = " << unprogrammed_sequence;
                        std::cout << " channel = " << std::setw(2) << std::setfill('0') << (word)channel;
                        std::cout << " data = " << std::setw(6) << (word)data;
                        std::cout << std::endl;
                        std::dec(std::cout);
                        */

                        if (channel == 015 || channel == 016 || (channel == 032 && !bitmask)) {
                            Agc::scaler.queue_dsky_update(channel, data);
                            // Reset RESTART light upon RESET key press
                            if (channel == 015 && data == 022) {
                                Agc::cpu.restart = false;
                            }
                        }
                    }
                }

                // If we're in a good state, write any new updated I/O channel data to it

                // Write the contents of channel 10, 11 and 12
                word chan10_data = Agc::cpu.read_io_channel(010);
                word chan11_data = Agc::cpu.read_io_channel(011);
                word chan12_data = Agc::cpu.read_io_channel(012);
                word chan13_data = Agc::cpu.read_io_channel(013);

                // Write channel 163 stuff for RESTART, OPR ERR, etc.
                word chan163_data = 0;

                // Check for KEY REL
                if ((chan11_data & BITMASK_5) && !Agc::scaler.dsky_flash_state()) {
                    chan163_data |= BITMASK_5;
                }
                // Check for verb/noun flashing
                if ((chan11_data & BITMASK_6) && Agc::scaler.dsky_flash_state()) {
                    chan163_data |= BITMASK_6;
                }
                // Check for OPR ERR
                if ((chan11_data & BITMASK_7) && !Agc::scaler.dsky_flash_state()) {
                    chan163_data |= BITMASK_7;
                }
                // Check for restart light
                if (Agc::cpu.restart) {
                    chan163_data |= BITMASK_8;
                }
                // Check for lights test signal
                if (chan13_data & BITMASK_10) {
                    chan163_data |= 1;
                    // Set the restart light and STBY light temporarily
                    chan163_data |= BITMASK_8;
                    chan163_data |= BITMASK_9;
                }
                // Check for TEMP light
                if (chan11_data & BITMASK_4) {
                    chan163_data |= BITMASK_4;
                }
                // Check for STBY light
                if (chan13_data & BITMASK_11) {
                    chan163_data |= BITMASK_9;
                }

                std::array<uint8_t, 4> chan10_buf = generate_dsky_packet(010, chan10_data);
                sock.write(chan10_buf.data(), 4);
                std::array<uint8_t, 4> chan11_buf = generate_dsky_packet(011, chan11_data);
                sock.write(chan11_buf.data(), 4);
                std::array<uint8_t, 4> chan12_buf = generate_dsky_packet(012, chan12_data);
                sock.write(chan12_buf.data(), 4);
                std::array<uint8_t, 4> chan13_buf = generate_dsky_packet(013, chan13_data);
                sock.write(chan13_buf.data(), 4);
                std::array<uint8_t, 4> chan163_buf = generate_dsky_packet(0163, chan163_data);
                sock.write(chan163_buf.data(), 4);
            }

            // Wait the remaining amount of time before checking the DSKY again
            std::this_thread::sleep_until(x);
        }
    } catch (std::runtime_error& err) {
        sock.close();
    }
}

std::array<uint8_t, 4> Timer::generate_dsky_packet(uint8_t channel, word data) {
    uint32_t packet_data = 0b00000000010000001000000011000000;  // pre-load the signature
    packet_data |= ((channel & 0b01111000) << 21);  // Upper bits of channel
    packet_data |= ((channel & 0b00000111) << 19);  // Lower bits of channel
    packet_data |= ((data & 0b0111000000000000) << 4);  // Upper bits of data
    packet_data |= ((data & 0b0000111111000000) << 2);  // Middle bits of data
    packet_data |= ((data & 0b0000000000111111));  // Lower bits of data

    std::array<uint8_t, 4> write_buf = {0, 0, 0, 0};
    write_buf[0] = (uint8_t)(packet_data >> 24);
    write_buf[1] = (uint8_t)(packet_data >> 16);
    write_buf[2] = (uint8_t)(packet_data >> 8);
    write_buf[3] = (uint8_t)(packet_data);

    /*
    if (channel != 0163 && data > 0) {
        std::oct(std::cout);
        std::cout << "from data " << std::setfill('0') << std::setw(6) << (word)channel << " " << std::setw(6) << data << std::endl;
        std::cout << "intermediary data " << std::setw(12) << packet_data << std::endl;
        std::cout << "generated packet";
        std::cout << " " << std::setw(3) << (word)write_buf[0];
        std::cout << " " << std::setw(3) << (word)write_buf[1];
        std::cout << " " << std::setw(3) << (word)write_buf[2];
        std::cout << " " << std::setw(3) << (word)write_buf[3];
        std::cout << std::endl;
        std::dec(std::cout);
    }
    */

    return write_buf;
}
}
