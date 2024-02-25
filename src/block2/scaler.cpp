#include "scaler.hpp"
#include "agc.hpp"

namespace agcplusplus::block2 {
Scaler::Scaler()
{
    cur_state = 0;
    prev_state = 0;
}

void Scaler::queue_dsky_update(word channel, word data) {
    dsky_queue.emplace(channel, data);
}

void Scaler::tick() {
    prev_state = cur_state;
    ++cur_state;

    bool F02B = (((cur_state & 2) ^ (prev_state & 2)) && (cur_state & 2) != 0);
    bool F05A = (((cur_state & BITMASK_5) ^ (prev_state & BITMASK_5)) && (cur_state & BITMASK_5) == 0);
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

    // Send 51.2 kpps tick rate to CDU
    if (F02B) {
        // Only send pulses to the CDU if CDU ZERO discrete is not present for that channel group
        // For ISS channels, AGC channel 12 bit 5. For OSS/LR/RR, channel 12 bit 1.
        Agc::cdu.tick_cmc();
    }

    // Process CDU commands from AGC, if their corresponding channel bit enables them.
    if (F05A) {
        const word chan14 = Agc::cpu.read_io_channel(014);
        if ((chan14 & BITMASK_15) != 0) {
            Agc::cpu.counters[COUNTER_CDUXD] = COUNT_DIRECTION_DOWN;
        }

        if ((chan14 & BITMASK_14) != 0) {
            Agc::cpu.counters[COUNTER_CDUYD] = COUNT_DIRECTION_DOWN;
        }

        if ((chan14 & BITMASK_13) != 0) {
            Agc::cpu.counters[COUNTER_CDUZD] = COUNT_DIRECTION_DOWN;
        }

        if ((chan14 & BITMASK_12) != 0) {
            Agc::cpu.counters[COUNTER_TRUND] = COUNT_DIRECTION_DOWN;
        }

        if ((chan14 & BITMASK_11) != 0) {
            Agc::cpu.counters[COUNTER_SHAFTD] = COUNT_DIRECTION_DOWN;
        }
    }

    // Process timer counts
    if (F06B) {
        // TIME6 only counts if the top bit of I/O channel 13 is set
        word check = Agc::cpu.read_io_channel(013);
        bool time6_enabled = ((check & BITMASK_16) != 0);   // Is bit 16 set?
        if (time6_enabled) {
            Agc::cpu.counters[COUNTER_TIME6] |= COUNT_DIRECTION_DOWN;
            //Agc::log_stream << "TIME6 decrement" << std::endl;
        }
    }

    if (F09B) {
        if ((cur_state & BITMASK_10) == 0) {    // if not FS10
            Agc::cpu.counters[COUNTER_TIME4] |= COUNT_DIRECTION_UP;
            //Agc::log_stream << "TIME4 increment" << std::endl;
        }

        // Generate KEYRUPT1, KEYRUPT2, or MARKRUPT if keys are pending
        // Read the DSKY queue
        if (!dsky_queue.empty()) {
            std::tuple<word, word> dsky_update = dsky_queue.front();
            word channel = std::get<0>(dsky_update);
            word data = std::get<1>(dsky_update);
            if (channel == 015 || channel == 016) {
                Agc::cpu.write_io_channel(channel, data);
                Agc::cpu.interrupts[RUPT_KEYRUPT1] = true;
                dsky_queue.pop();
            } else if (channel == 032) {
                word chan32 = Agc::cpu.read_io_channel(channel);
                chan32 &= ~BITMASK_14;  // Mask out bit 14 due to inverted logic
                chan32 |= (~(data << 1) & BITMASK_14);
                Agc::cpu.write_io_channel(channel, chan32);
                //Agc::cpu.interrupts[RUPT_KEYRUPT1] = true;
                dsky_queue.pop();
            }
        }
    }

    if (F10A) {
         Agc::cpu.counters[COUNTER_TIME5] |= COUNT_DIRECTION_UP;
         //Agc::log_stream << "TIME5 increment" << std::endl;

        // Start radar cycle if enabled

        // Trigger restart if TC TRAP flip flop is set
        if ((!tc_started || !tc_ended) && !Agc::config.ignore_alarms) {
            Agc::log_stream << "HARDWARE ALARM: TC TRAP" << std::endl;
            Agc::cpu.write_io_channel(077, BITMASK_3);
            Agc::cpu.queue_gojam();
        }
    }

    if (F10B) {
        Agc::cpu.counters[COUNTER_TIME1] |= COUNT_DIRECTION_UP;
        Agc::cpu.counters[COUNTER_TIME3] |= COUNT_DIRECTION_UP;
        //Agc::log_stream << "TIME1+3 increment" << std::endl;

        tc_started = false;
        tc_ended = false;
    }

    if (F14B) {
        interrupt_ended = false;
        interrupt_started = false;
    }

    if (F17A) {
        if (!Agc::cpu.night_watchman && !Agc::config.ignore_alarms) {
            Agc::log_stream << "HARDWARE ALARM: NIGHT WATCHMAN" << std::endl;
            Agc::cpu.write_io_channel(077, BITMASK_5);
            Agc::cpu.queue_gojam();
        }
    }

    if (F17B) {
        Agc::cpu.night_watchman = false;
    }

    if (!FS16 && !FS17) {
        dsky_flash_on = true;
    } else {
        dsky_flash_on = false;
    }

    if (F14H) {
        // If an old interrupt is still going or a new one hasn't started, alarm
        if (!interrupt_started && !interrupt_ended && !Agc::config.ignore_alarms) {
            Agc::log_stream << "HARDWARE ALARM: RUPT LOCK" << std::endl;
            Agc::cpu.write_io_channel(077, BITMASK_4);
            Agc::cpu.queue_gojam();
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

void Scaler::signal_tc_started() {
    tc_started = true;
}

void Scaler::signal_tc_ended() {
    tc_ended = true;
}
}
