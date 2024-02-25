#include "agc.hpp"
#include "subinstructions.hpp"
#include "sockpp/tcp_socket.h"
#include "sockpp/tcp_acceptor.h"

#include <utility>

namespace agcplusplus::block1 {
    Timer Agc::timer;
    Scaler Agc::scaler;
    Memory Agc::memory;
    Cpu Agc::cpu;
    InitArguments Agc::configuration;
    std::ofstream Agc::log_stream;

    Agc::Agc(std::vector<word> rope_buffer, InitArguments init_args) {
        memory.assign_fixed_memory(std::move(rope_buffer));
        configuration = init_args;

        // Set up log output stream.
        log_stream.open("AGCPlusPlus.log");

        cpu.go();
    }

    [[noreturn]] void Agc::run() {
        cpu.current_subinstruction = subinstruction_data[0];
        // Start a thread where we can look for incoming connections
        std::thread socket_thread(&Agc::accept_dsky_connections, *this);

        // Start ticking our various functions at their given intervals
        std::cout << "Computer started." << std::endl;
        while (true) {
            timer.execute_tick_batch();
        }
    }

    [[noreturn]] void Agc::accept_dsky_connections() {
        while (true) {
            // Set up the socket to connect to the DSKY server
            sockpp::socket_initializer::initialize();
            in_port_t port = 19671;
            sockpp::tcp_acceptor dsky_conn(port);

            // Update the DSKY client connection
            sockpp::inet_address peer;
            sockpp::tcp_socket sock = dsky_conn.accept(&peer);
            std::cout << "DSKY connection from " << peer << std::endl;

            if (!sock) {
                std::cerr << "Error accepting connection!" << std::endl;
            } else {
                std::thread dsky_thread(&Agc::process_dsky, *this, std::move(sock));
                dsky_thread.detach();
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void Agc::process_dsky(sockpp::tcp_socket sock) {
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


                            if ((channel == 04 || channel == 05) && !bitmask && !unprogrammed_sequence) {
                                scaler.dsky_queue.emplace(std::tuple(channel, data));
                                // Reset RESTART light upon RESET key press
                                if (channel == 015 && data == 022) {
                                    //cpu_ref->restart = false;
                                }
                            }
                        }
                    }

                    // If we're in a good state, write any new updated I/O channel data to it

                    // Write the contents of OUT0 and OUT1
                    word out0_data = cpu.out[0];
                    word out1_data = cpu.out[1];

                    std::array<uint8_t, 4> out0_buf = generate_dsky_packet(010, out0_data);
                    sock.write(out0_buf.data(), 4);
                    std::array<uint8_t, 4> out1_buf = generate_dsky_packet(011, out1_data);
                    sock.write(out1_buf.data(), 4);
                }

                // Wait the remaining amount of time before checking the DSKY again
                std::this_thread::sleep_until(x);
            }
        } catch (std::runtime_error& err) {
            sock.close();
        }
    }

    std::array<uint8_t, 4> Agc::generate_dsky_packet(uint8_t channel, word data) {
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