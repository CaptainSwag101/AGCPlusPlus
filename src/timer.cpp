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
        std::thread dsky_thread(&Timer::read_dsky, *this, std::move(sock));
        dsky_thread.detach();
    }
}

void Timer::read_dsky(sockpp::tcp_socket sock) {
    while (true) {
        if (sock.is_open()) {
            char buf[4];
            size_t result = sock.read(buf, 4);
            if (result == -1 || result == 0) {
                std::cout << "Read fail, disconnecting..." << std::endl;
                sock.close();
                break;
            } else {
                uint8_t channel = (buf[1] >> 3);
                uint8_t misc = (buf[1] & 7) >> 1;   // if 1, PRO key state is pressed, if 0, released.
                uint8_t keycode = (buf[3] & 037);
                std::cout << "Read success (result = " << result << "), packet data is:" << std::endl;
                std::oct(std::cout);
                std::cout << " channel = " << std::setw(2) << std::setfill('0') << (word)channel;
                std::cout << " misc = " << (word)misc;
                std::cout << " keycode = " << std::setw(2) << (word)keycode;
                std::cout << std::endl;
                std::dec(std::cout);

                if (channel == 015) {
                    scaler_ref->queue_dsky_update(channel, keycode);
                } else if (channel == 012) {
                    scaler_ref->queue_dsky_update(channel, misc);
                }
            }
        }
    }
}
}
