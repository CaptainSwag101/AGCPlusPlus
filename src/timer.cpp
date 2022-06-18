#include "timer.hpp"
#include <functional>
#include <thread>

namespace agcplusplus {
Timer::Timer() {
    std::cout << "Initializing timer..." << std::endl;

    total_ticks = 0;

    std::cout << "Initializing timer done." << std::endl;
}

void Timer::assign_cpu(std::shared_ptr<Cpu> cpu) {
    cpu_ref = cpu;
}

void Timer::assign_memory(std::shared_ptr<Memory> mem) {
    memory_ref = mem;
}

void Timer::assign_scaler(std::shared_ptr<Scaler> scaler) {
    scaler_ref = scaler;
}

void Timer::start_timer() {
    stop = false;

    if (!cpu_ref) {
        std::cerr << "Timer CPU reference has not been assigned." << std::endl;
        return;
    }

    if (!memory_ref) {
        std::cerr << "Timer memory reference has not been assigned." << std::endl;
        return;
    }

    // Start a thread where we can look for incoming connections
    std::thread socket_thread(&Timer::accept_dsky_connections, *this);

    // Start ticking our various functions at their given intervals
    std::cout << "Starting CPU clock." << std::endl;
    while (!stop) {
        // Calculate the time that we should tick the clock next, before any code executes
        auto started_at = std::chrono::steady_clock::now();
        auto x = started_at + std::chrono::milliseconds(1); // We can complete 1024 timepulses in 1 millisecond

        for (word t = 0; t < TIMEPULSES_PER_MILLISECOND; ++t) {
            ++total_ticks;

            // Perform CPU timepulse every tick
            cpu_ref->tick();

            // Tick the scaler every 10 ticks (every 10 milliseconds)
            if ((total_ticks % 10) == 0) {
                scaler_ref->tick();
            }

            // Other ticks go here
        }

        auto ended_at = std::chrono::steady_clock::now();
        auto batch_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(ended_at - started_at);

        //std::cout << "Batched ticks took " << (batch_duration.count() / 1000000.0) << " milliseconds." << std::endl;

        // DEBUG: Stop timer after 1 second
        if ((total_ticks % (TIMEPULSES_PER_MILLISECOND * 10000)) == 0) {
            //stop_timer();
        }

        // Wait the remaining amount of time before ticking the clock again
        std::this_thread::sleep_until(x);
    }
}

void Timer::stop_timer() {
    std::cout << "Stopping main clock after " << total_ticks << " ticks." << std::endl;
    stop = true;
}

void Timer::accept_dsky_connections() {
    while (!stop) {
        // Set up the socket to connect to the DSKY server
        sockpp::socket_initializer sock_init;
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
    sock.set_non_blocking(true);
    while (!stop) {
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
                    std::cout << "DSKY read success (result = " << result << "), packet data is:" << std::endl;
                    std::oct(std::cout);
                    std::cout << " u = " << bitmask;
                    std::cout << " t = " << unprogrammed_sequence;
                    std::cout << " channel = " << std::setw(2) << std::setfill('0') << (word)channel;
                    std::cout << " data = " << std::setw(6) << (word)data;
                    std::cout << std::endl;
                    std::dec(std::cout);

                    if (channel == 015 || channel == 016) {
                        scaler_ref->queue_dsky_update(channel, data);
                    } else if (channel == 012) {

                    }
                }
            }

            // If we're in a good state, write any new updated I/O channel data to it
            uint8_t write_channel = 0;
            word write_data = 0;
            std::array<char, 4> write_buf = {};

            // Write the contents of channel 10, 11 and 12
            write_channel = 010;
            write_data = cpu_ref->read_io_channel(write_channel);
            write_buf = generate_dsky_packet(write_channel, write_data);
            sock.write(write_buf.data(), 4);

            write_channel = 011;
            write_data = cpu_ref->read_io_channel(write_channel);
            write_buf = generate_dsky_packet(write_channel, write_data);
            sock.write(write_buf.data(), 4);

            write_channel = 012;
            write_data = cpu_ref->read_io_channel(write_channel);
            write_buf = generate_dsky_packet(write_channel, write_data);
            sock.write(write_buf.data(), 4);

            // Write channel 163 stuff for RESTART, OPR ERR, etc.
            write_channel = 0163;
            write_data = 0;
            if (cpu_ref->restart) {
                write_data |= 0b010000000;
            }
            write_buf = generate_dsky_packet(write_channel, write_data);
            sock.write(write_buf.data(), 4);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

std::array<char, 4> Timer::generate_dsky_packet(uint8_t channel, word data) {
    std::array<char, 4> write_buf = {0, 0, 0, 0};

    write_buf[0] |= channel >> 3;
    write_buf[1] |= (0b01000000 | ((channel & 7) << 3));
    write_buf[2] |= (0b10000000 | ((data >> 6)));
    write_buf[3] |= 0b11000000 | ((uint8_t)(data));

    return write_buf;
}
}
