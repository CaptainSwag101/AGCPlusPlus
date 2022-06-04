#include "timer.hpp"
#include <functional>
#include <thread>

namespace agcplusplus {
Timer::Timer() {
    std::cout << "Initializing timer..." << std::endl;

    total_ticks = 0;

    std::cout << "Initializing timer done." << std::endl;
}

void Timer::assign_cpu(Cpu& cpu) {
    cpu_ref = std::make_shared<Cpu>(cpu);
}

void Timer::assign_memory(Memory& mem) {
    memory_ref = std::make_shared<Memory>(mem);
}

void Timer::assign_scaler(Scaler& scaler) {
    scaler_ref = std::make_shared<Scaler>(scaler);
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

    if (!scaler_ref) {
        std::cerr << "Timer scaler reference has not been assigned." << std::endl;
        return;
    }

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

            // Tick the scaler every 10 ticks
            if ((total_ticks % 10) == 0) {
                scaler_ref->tick();
            }

            // Other ticks go here
        }

        // DEBUG: Stop timer after 9 batched tick periods
        if ((total_ticks % (TIMEPULSES_PER_MILLISECOND * 9)) == 0) {
            stop_timer();
        }

        // Wait the remaining amount of time before ticking the clock again
        std::this_thread::sleep_until(x);
    }
}

void Timer::stop_timer() {
    std::cout << "Stopping main clock after " << total_ticks << " ticks." << std::endl;
    stop = true;
}
}
