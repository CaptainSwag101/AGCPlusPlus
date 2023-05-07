#include "scaler.hpp"
#include "agc.hpp"

namespace agcplusplus::block1 {
    void Scaler::tick() {
        // Tick our divider stages
        previous_tick = current_tick;
        current_tick += 1;

        bool F10A = (((current_tick & BITMASK_10) ^ (previous_tick & BITMASK_10)) && (current_tick & BITMASK_10) == 0);
        bool F10B = (((current_tick & BITMASK_10) ^ (previous_tick & BITMASK_10)) && (current_tick & BITMASK_10) != 0);

        if (F10A) {
            Agc::cpu.counters[COUNTER_TIME1] = COUNTER_STATUS::UP;
            Agc::cpu.counters[COUNTER_TIME3] = COUNTER_STATUS::UP;
        }

        if (F10B) {
            Agc::cpu.counters[COUNTER_TIME4] = COUNTER_STATUS::UP;
        }
    }
}