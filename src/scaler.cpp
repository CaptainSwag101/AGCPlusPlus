#include "scaler.hpp"

namespace agcplusplus {
Scaler::Scaler()
{
    std::cout << "Initializing scaler..." << std::endl;

    cur_state = 0;
    prev_state = 0;

    std::cout << "Initializing scaler done." << std::endl;
}

void Scaler::assign_cpu(std::shared_ptr<Cpu> cpu)
{
    cpu_ref = cpu;
}

void Scaler::tick() {
    if (!cpu_ref) {
        std::cerr << "Scaler CPU reference has not been assigned." << std::endl;
        return;
    }

    prev_state = cur_state;
    ++cur_state;

    //bool F01B = (((cur_state & 1) ^ (prev_state & 1)) && (cur_state & 1) != 0);
    bool F06B = (((cur_state & BITMASK_6) ^ (prev_state & BITMASK_6)) && (cur_state & BITMASK_6) != 0);
    bool F09B = (((cur_state & BITMASK_9) ^ (prev_state & BITMASK_9)) && (cur_state & BITMASK_9) != 0);
    bool F10A = (((cur_state & BITMASK_10) ^ (prev_state & BITMASK_10)) && (cur_state & BITMASK_10) == 0);
    bool F10B = (((cur_state & BITMASK_10) ^ (prev_state & BITMASK_10)) && (cur_state & BITMASK_10) != 0);

    // Process timer counts
    if (F06B) {
        //cpu_ref->counters[COUNTER_TIME6] |= COUNTER_DIRECTION_DOWN;
    }

    if (F09B) {
        if ((cur_state & BITMASK_10) == 0) {    // if not FS10
            cpu_ref->counters[COUNTER_TIME4] |= COUNT_DIRECTION_UP;
        }

        // Generate KEYRUPT1, KEYRUPT2, or MARKRUPT if keys are pending
        // Read
    }

    if (F10A) {
         cpu_ref->counters[COUNTER_TIME5] |= COUNT_DIRECTION_UP;

        // Start radar cycle if enabled
        // Trigger restart if TC TRAP flip flop is set
    }

    if (F10B) {
        cpu_ref->counters[COUNTER_TIME1] |= COUNT_DIRECTION_UP;
        cpu_ref->counters[COUNTER_TIME3] |= COUNT_DIRECTION_UP;
    }
}
}
