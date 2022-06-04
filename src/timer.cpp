#include "timer.hpp"
#include <functional>
#include <thread>

namespace agcplusplus {
Timer::Timer() {
    total_ticks = 0;
}

void Timer::assign_cpu(Cpu& cpu) {
    cpu_ref = std::make_shared<Cpu>(cpu);
}

void Timer::assign_memory(Memory& mem) {
    memory_ref = std::make_shared<Memory>(mem);
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

    // Start ticking our various functions at their given intervals
    while (!stop) {
        // Perform CPU timepulse every two ticks
        if ((total_ticks % 2) == 0) {
            cpu_ref->tick();
        }

        ++total_ticks;

        // DEBUG: Stop timer after 10,000 ticks
        if ((total_ticks % 10000) == 0) {
            stop_timer();
        }

        // Wait the specified amount of time before ticking the clock again
        auto x = std::chrono::nanoseconds(1000000000 / FREQUENCY_MAIN_CLOCK);
        std::this_thread::sleep_for(x);
    }
}

void Timer::stop_timer() {
    stop = true;
}
}
