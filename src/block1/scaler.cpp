#include "scaler.hpp"
#include "agc.hpp"

namespace agcplusplus::block1 {
    void Scaler::tick() {
        // Tick our divider stages
        previous_tick = current_tick;
        current_tick += 1;

        bool F09B = (((current_tick & BITMASK_9) ^ (previous_tick & BITMASK_9)) && (current_tick & BITMASK_9) != 0);
        bool F10A = (((current_tick & BITMASK_10) ^ (previous_tick & BITMASK_10)) && (current_tick & BITMASK_10) == 0);
        bool F10B = (((current_tick & BITMASK_10) ^ (previous_tick & BITMASK_10)) && (current_tick & BITMASK_10) != 0);

        if (F09B) {
            // Generate KEYRUPT if keys are pending
            if (!dsky_queue.empty()) {
                auto dsky_update = dsky_queue.front();
                word channel = std::get<0>(dsky_update);
                word data = std::get<1>(dsky_update);
                if (channel == 4 || channel == 5) {
                    if (data != 0) {
                        Agc::cpu.in[channel - 4] = data;
                        Agc::cpu.interrupts[RUPT_KEYRUPT] = true;
                        //std::cout << "KEYRUPT" << std::endl;
                    }
                    dsky_queue.pop();
                }
            }
        }


        if (F10A) {
            Agc::timer.debug_end_tick = Agc::timer.total_ticks;
            double duration = (Agc::timer.debug_end_tick - Agc::timer.debug_start_tick * 1.0) / Timer::TIMEPULSES_PER_MILLISECOND;
            if (duration != 10.0)
                std::cout << "TIME3 increment took a bad amount of time! " << duration << " milliseconds" << std::endl;
            Agc::cpu.counters[COUNTER_TIME1] = COUNTER_STATUS::UP;
            Agc::cpu.counters[COUNTER_TIME3] = COUNTER_STATUS::UP;
            Agc::timer.debug_start_tick = Agc::timer.total_ticks;
        }

        if (F10B) {
            Agc::cpu.counters[COUNTER_TIME4] = COUNTER_STATUS::UP;
        }
    }
}