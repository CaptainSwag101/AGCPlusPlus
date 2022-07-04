#include "scaler.hpp"

namespace agcplusplus {
Scaler::Scaler(InitArguments init_args)
{
    std::cout << "Initializing scaler..." << std::endl;

    config = init_args;
    cur_state = 0;
    prev_state = 0;

    std::cout << "Initializing scaler done." << std::endl;
}

void Scaler::assign_cpu(std::shared_ptr<Cpu> cpu)
{
    cpu_ref = cpu;
}

void Scaler::queue_dsky_update(word channel, word data) {
    dsky_queue.push({channel, data});
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
    bool F12B = (((cur_state & BITMASK_12) ^ (prev_state & BITMASK_12)) && (cur_state & BITMASK_12) != 0);
    bool F14B = (((cur_state & BITMASK_14) ^ (prev_state & BITMASK_14)) && (cur_state & BITMASK_14) != 0);
    bool F17A = (((cur_state & BITMASK_17) ^ (prev_state & BITMASK_17)) && (cur_state & BITMASK_17) == 0);
    bool F17B = (((cur_state & BITMASK_17) ^ (prev_state & BITMASK_17)) && (cur_state & BITMASK_17) != 0);
    bool FS13 = ((cur_state & BITMASK_13) != 0);
    bool FS14 = ((cur_state & BITMASK_14) != 0);
    bool FS16 = ((cur_state & BITMASK_16) != 0);
    bool FS17 = ((cur_state & BITMASK_17) != 0);
    bool F14H = (F12B && FS13 && !FS14);    // Used for RUPT lock check

    // Process timer counts
    if (F06B) {
        // TIME6 only counts if the top bit of I/O channel 13 is set
        word check = cpu_ref->read_io_channel(013);
        bool time6_enabled = ((check & BITMASK_16) != 0);   // Is bit 16 set?
        if (time6_enabled) {
            cpu_ref->counters[COUNTER_TIME6] |= COUNT_DIRECTION_DOWN;
            //std::cout << "TIME6 decrement" << std::endl;
        }
    }

    if (F09B) {
        if ((cur_state & BITMASK_10) == 0) {    // if not FS10
            cpu_ref->counters[COUNTER_TIME4] |= COUNT_DIRECTION_UP;
            //std::cout << "TIME4 increment" << std::endl;
        }

        // Generate KEYRUPT1, KEYRUPT2, or MARKRUPT if keys are pending
        // Read the DSKY queue
        if (!dsky_queue.empty()) {
            std::tuple<word, word> dsky_update = dsky_queue.front();
            word channel = std::get<0>(dsky_update);
            word data = std::get<1>(dsky_update);
            if (channel == 015 || channel == 016) {
                cpu_ref->write_io_channel(channel, data);
                cpu_ref->interrupts[RUPT_KEYRUPT1] = true;
                dsky_queue.pop();
            } else if (channel == 032) {
                word chan32 = cpu_ref->read_io_channel(channel);
                chan32 &= ~BITMASK_14;  // Mask out bit 14 due to inverted logic
                chan32 |= (~(data << 1) & BITMASK_14);
                cpu_ref->write_io_channel(channel, chan32);
                //cpu_ref->interrupts[RUPT_KEYRUPT1] = true;
                dsky_queue.pop();
            }
        }
    }

    if (F10A) {
         cpu_ref->counters[COUNTER_TIME5] |= COUNT_DIRECTION_UP;
         //std::cout << "TIME5 increment" << std::endl;

        // Start radar cycle if enabled
        // Trigger restart if TC TRAP flip flop is set
    }

    if (F10B) {
        cpu_ref->counters[COUNTER_TIME1] |= COUNT_DIRECTION_UP;
        cpu_ref->counters[COUNTER_TIME3] |= COUNT_DIRECTION_UP;
        //std::cout << "TIME1+3 increment" << std::endl;
    }

    if (F14B) {
        interrupt_ended = false;
        interrupt_started = false;
    }

    if (F17A) {
        if (!cpu_ref->night_watchman && !config.ignore_alarms) {
            std::cout << "HARDWARE ALARM: NIGHT WATCHMAN" << std::endl;
            cpu_ref->write_io_channel(077, BITMASK_5);
            cpu_ref->queue_gojam();
        }
    }

    if (F17B) {
        cpu_ref->night_watchman = false;
    }

    if (!FS16 && !FS17) {
        dsky_flash_on = true;
    } else {
        dsky_flash_on = false;
    }

    if (F14H) {
        // If an old interrupt is still going or a new one hasn't started, alarm
        if (!interrupt_started && !interrupt_ended && !config.ignore_alarms) {
            std::cout << "HARDWARE ALARM: RUPT LOCK" << std::endl;
            cpu_ref->write_io_channel(077, BITMASK_4);
            cpu_ref->queue_gojam();
        }
    }
}

bool Scaler::dsky_flash_state() {
    return dsky_flash_on;
}

void Scaler::update_interrupt_state(bool new_iip) {
    // If our interrupt state has changed, set the relevant flip-flop
    if (last_iip && !new_iip) {
        interrupt_ended = true;
    } else if (!last_iip && new_iip) {
        interrupt_started = true;
    }

    last_iip = new_iip;
}
}
