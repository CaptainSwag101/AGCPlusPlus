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
        bool F14A = (((current_tick & BITMASK_14) ^ (previous_tick & BITMASK_14)) && (current_tick & BITMASK_14) == 0);
        bool F14B = (((current_tick & BITMASK_14) ^ (previous_tick & BITMASK_14)) && (current_tick & BITMASK_14) != 0);


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
                    }
                    dsky_queue.pop();
                }
            }
        }

        if (F10A) {
            Agc::cpu.counters[COUNTER_TIME1] = COUNTER_STATUS::UP;
            Agc::cpu.counters[COUNTER_TIME3] = COUNTER_STATUS::UP;
        }

        if (F10B) {
            Agc::cpu.counters[COUNTER_TIME4] = COUNTER_STATUS::UP;
        }

        if (F14A) {
            nrptal_disarm = false;
        }

        if (F14B) {
            if (!nrptal_disarm) {
                std::cout << "RUPT LOCK: NO RUPTS IN 80ms" << std::endl;
                Agc::cpu.queue_gojam();
            }
        }
    }

    void Scaler::interrupt_active() {
        nrptal_disarm = true;
    }
}