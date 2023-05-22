#include "agc.hpp"
#include "timer.hpp"

#include <chrono>
#include <thread>

namespace agcplusplus::block1 {
    void Timer::execute_tick_batch() {
        // Calculate the time that we should tick the clock next, before any code executes
        auto started_at = std::chrono::steady_clock::now();
        auto x = started_at + std::chrono::milliseconds(1); // We can complete 1024 timepulses in 1 millisecond

        for (auto t = 0; t < TIMEPULSES_PER_MILLISECOND; ++t) {
            tick();
        }

        auto ended_at = std::chrono::steady_clock::now();

        //auto batch_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(ended_at - started_at);
        //std::cout << "Batched ticks took " << (batch_duration.count() / 1000000.0) << " milliseconds." << std::endl;

        // Wait the remaining amount of time before ticking the clock again
        std::this_thread::sleep_until(x);
    }

    void Timer::tick() {
        ++total_ticks;

        // Perform CPU timepulse every tick
        Agc::cpu.tick();

        // Tick the scaler every 10 ticks (every 10 milliseconds)
        if ((total_ticks % 10) == 0) {
            Agc::scaler.tick();
        }

        // Other ticks go here
    }
}