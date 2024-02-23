#include "cdu.hpp"

#include <cmath>
#include <iostream>

#include "agc.hpp"

namespace agcplusplus::block2 {
    double CduChannel::coarse_error() const {
        const double cos_voltage = std::cos(theta) * CDU_VOLTAGE;
        const double sin_voltage = std::sin(theta) * CDU_VOLTAGE;

        // Determine the output at the op-amp by summing up the coarse system switches,
        // per the DC1-DC12 logic dependent on the set bits of the read counter.
        double amplifier_output = 0.0;

        // Figure out what appropriate conditions for any of the switches have been met.
        // Sine section.
        if ((read_counter & COARSE_S1_MASK) == (COARSE_S1_VALUE1 & COARSE_S1_MASK) ||
            (read_counter & COARSE_S1_MASK) == (COARSE_S1_VALUE2 & COARSE_S1_MASK)) {
            amplifier_output += -sin_voltage * COARSE_S1_RESISTOR;
        }
        if ((read_counter & COARSE_S2_MASK) == (COARSE_S2_VALUE1 & COARSE_S2_MASK) ||
            (read_counter & COARSE_S2_MASK) == (COARSE_S2_VALUE2 & COARSE_S2_MASK)) {
            amplifier_output += -sin_voltage * COARSE_S2_RESISTOR;
        }
        if ((read_counter & COARSE_S3_MASK) == (COARSE_S3_VALUE1 & COARSE_S3_MASK) ||
            (read_counter & COARSE_S3_MASK) == (COARSE_S3_VALUE2 & COARSE_S3_MASK)) {
            amplifier_output += sin_voltage * COARSE_S3_RESISTOR;
        }
        if ((read_counter & COARSE_S4_MASK) == (COARSE_S4_VALUE1 & COARSE_S4_MASK) ||
            (read_counter & COARSE_S4_MASK) == (COARSE_S4_VALUE2 & COARSE_S4_MASK)) {
            amplifier_output += sin_voltage * COARSE_S4_RESISTOR;
        }
        // Cosine section.
        if ((read_counter & COARSE_S5_MASK) == (COARSE_S5_VALUE1 & COARSE_S5_MASK) ||
            (read_counter & COARSE_S5_MASK) == (COARSE_S5_VALUE2 & COARSE_S5_MASK)) {
            amplifier_output += -cos_voltage * COARSE_S5_RESISTOR;
        }
        if ((read_counter & COARSE_S6_MASK) == (COARSE_S6_VALUE1 & COARSE_S6_MASK) ||
            (read_counter & COARSE_S6_MASK) == (COARSE_S6_VALUE2 & COARSE_S6_MASK)) {
            amplifier_output += -cos_voltage * COARSE_S6_RESISTOR;
        }
        if ((read_counter & COARSE_S7_MASK) == (COARSE_S7_VALUE1 & COARSE_S7_MASK) ||
            (read_counter & COARSE_S7_MASK) == (COARSE_S7_VALUE2 & COARSE_S7_MASK)) {
            amplifier_output += cos_voltage * COARSE_S7_RESISTOR;
        }
        if ((read_counter & COARSE_S8_MASK) == (COARSE_S8_VALUE1 & COARSE_S8_MASK) ||
            (read_counter & COARSE_S8_MASK) == (COARSE_S8_VALUE2 & COARSE_S8_MASK)) {
            amplifier_output += cos_voltage * COARSE_S8_RESISTOR;
        }
        // Ladder switches.
        if ((read_counter & COARSE_S9_MASK) == (COARSE_S9_VALUE & COARSE_S9_MASK)) {
            amplifier_output += CDU_VOLTAGE * COARSE_S9_RESISTOR;
        }
        if ((read_counter & COARSE_S10_MASK) == (COARSE_S10_VALUE & COARSE_S10_MASK)) {
            amplifier_output += -CDU_VOLTAGE * COARSE_S10_RESISTOR;
        }
        if ((read_counter & COARSE_S11_MASK) == (COARSE_S11_VALUE & COARSE_S11_MASK)) {
            amplifier_output += -CDU_VOLTAGE * COARSE_S11_RESISTOR;
        }
        if ((read_counter & COARSE_S12_MASK) == (COARSE_S12_VALUE & COARSE_S12_MASK)) {
            amplifier_output += -CDU_VOLTAGE * COARSE_S12_RESISTOR;
        }

        return amplifier_output;
    }

    double CduChannel::fine_error(double msa_gain) const {
        // 16X resolver speed
        double cos_voltage = std::cos(16.0 * theta);
        double sin_voltage = std::sin(16.0 * theta);

        // Switch booleans
        const bool S1 = (read_counter & FINE_S1_MASK) == (FINE_S1_VALUE1 & FINE_S1_MASK) ||
            (read_counter & FINE_S1_MASK) == (FINE_S1_VALUE2 & FINE_S1_MASK);
        const bool S2 = (read_counter & FINE_S2_MASK) == (FINE_S2_VALUE1 & FINE_S2_MASK) ||
            (read_counter & FINE_S2_MASK) == (FINE_S2_VALUE2 & FINE_S2_MASK);
        const bool S3 = (read_counter & FINE_S3_MASK) == (FINE_S3_VALUE1 & FINE_S3_MASK) ||
            (read_counter & FINE_S3_MASK) == (FINE_S3_VALUE2 & FINE_S3_MASK);
        const bool S4 = (read_counter & FINE_S4_MASK) == (FINE_S4_VALUE1 & FINE_S4_MASK) ||
            (read_counter & FINE_S4_MASK) == (FINE_S4_VALUE2 & FINE_S4_MASK);
        const bool S5 = (read_counter & FINE_S5_MASK) == (FINE_S5_VALUE1 & FINE_S5_MASK) ||
            (read_counter & FINE_S5_MASK) == (FINE_S5_VALUE2 & FINE_S5_MASK);
        const bool S6 = (read_counter & FINE_S6_MASK) == (FINE_S6_VALUE1 & FINE_S6_MASK) ||
            (read_counter & FINE_S6_MASK) == (FINE_S6_VALUE2 & FINE_S6_MASK);
        const bool S7 = (read_counter & FINE_S7_MASK) == (FINE_S7_VALUE & FINE_S7_MASK);
        const bool S8 = (read_counter & FINE_S8_MASK) == (FINE_S8_VALUE & FINE_S8_MASK);
        const bool S9 = (read_counter & FINE_S9_MASK) == (FINE_S9_VALUE & FINE_S9_MASK);
        const bool S10 = (read_counter & FINE_S10_MASK) == (FINE_S10_VALUE & FINE_S10_MASK);
        const bool S11 = (read_counter & FINE_S11_MASK) == (FINE_S11_VALUE & FINE_S11_MASK);
        const bool S12 = (read_counter & FINE_S12_MASK) == (FINE_S12_VALUE & FINE_S12_MASK);
        const bool S13 = (read_counter & FINE_S13_MASK) == (FINE_S13_VALUE & FINE_S13_MASK);
        const bool S14 = (read_counter & FINE_S14_MASK) == (FINE_S14_VALUE & FINE_S14_MASK);
        const bool S15 = (read_counter & FINE_S15_MASK) == FINE_S15_MASK;
        const bool S16 = (read_counter & FINE_S16_MASK) == FINE_S16_MASK;
        const bool S17 = (read_counter & FINE_S17_MASK) == FINE_S17_MASK;
        const bool S18 = (read_counter & FINE_S18_MASK) == FINE_S18_MASK;
        const bool S19 = (read_counter & FINE_S19_MASK) == FINE_S19_MASK;
        const bool S20 = (read_counter & FINE_S20_MASK) == FINE_S20_MASK;
        const bool S21 = (read_counter & FINE_S21_MASK) == FINE_S21_MASK;
        //const bool S22 = unknown_trunnion_thing;

        // Invert voltages per switch logic
         if (S6) {
            sin_voltage = -sin_voltage;
        }
        if (S8) {
            cos_voltage = -cos_voltage;
        }

        // This is the final voltage sent to the MSA
        double junction_voltage = 0.0;

        // Main summing amplifier
        if (S1) {
            junction_voltage += cos_voltage * FINE_SIN_11_25;
            junction_voltage += sin_voltage * FINE_COS_11_25;
        }
        if (S2) {
            junction_voltage += cos_voltage * FINE_SIN_33_75;
            junction_voltage += sin_voltage * FINE_COS_33_75;
        }
        if (S3) {
            junction_voltage += cos_voltage * FINE_SIN_56_25;
            junction_voltage += sin_voltage * FINE_COS_56_25;
        }
        if (S4) {
            junction_voltage += cos_voltage * FINE_SIN_78_75;
            junction_voltage += sin_voltage * FINE_COS_78_75;
        }

        // Cos and Sin amplifier
        double cos_amp_voltage = 0.0;
        double sin_amp_voltage = 0.0;
        if (S1) {
            cos_amp_voltage += cos_voltage * FINE_COS_11_25;
            sin_amp_voltage += sin_voltage * FINE_SIN_11_25;
        }
        if (S2) {
            cos_amp_voltage += cos_voltage * FINE_COS_33_75;
            sin_amp_voltage += sin_voltage * FINE_SIN_33_75;
        }
        if (S3) {
            cos_amp_voltage += cos_voltage * FINE_COS_56_25;
            sin_amp_voltage += sin_voltage * FINE_SIN_56_25;
        }
        if (S4) {
            cos_amp_voltage += cos_voltage * FINE_COS_78_75;
            sin_amp_voltage += sin_voltage * FINE_SIN_78_75;
        }
        // Only S11 OR S14 may be active at a time.
        // Addition is actually subtraction because the amplifiers invert.
        if (S11) {
            cos_amp_voltage -= sin_amp_voltage;
        }
        if (S14) {
            sin_amp_voltage -= cos_amp_voltage;
        }

        // Inverted amplifiers
        cos_amp_voltage = -cos_amp_voltage;
        sin_amp_voltage = -sin_amp_voltage;

        // Ladder amplifier
        double ladder_amp_voltage = 0.0;
        // Only (S9 OR S10) OR (S12 OR S13) may be active at a time.
        if (S9) {
            ladder_amp_voltage += sin_amp_voltage;
            junction_voltage += sin_amp_voltage * FINE_11_25_BIT;
        }
        if (S10) {
            ladder_amp_voltage += sin_amp_voltage;
            junction_voltage += sin_amp_voltage * FINE_BIAS * FINE_240K;
        }
        if (S12) {
            ladder_amp_voltage += cos_amp_voltage;
            junction_voltage += cos_amp_voltage * FINE_11_25_BIT;
        }
        if (S13) {
            ladder_amp_voltage += cos_amp_voltage;
            junction_voltage += cos_amp_voltage * FINE_BIAS * FINE_240K;
        }
        ladder_amp_voltage = -ladder_amp_voltage;   // Invert to be in-phase
        // Do K*sin(psi) by adding up the angles for switches S15-S22 and then performing sin() on that.
        double mult = 0.0;
        if (S15) mult += (2600.0 / 6600.0) * 0.25;  // Voltage divider * 25K/100K MSA gain
        if (S16) mult += (1960.0 / 9960.0) * 0.25;
        if (S17) mult += (867.0 / 8867.0) * 0.25;
        if (S18) mult += (409.0 / 8409.0) * 0.25;
        if (S19) mult += (399.0 / 16399.0) * 0.25;
        if (S20) mult += (197.0 / 16197.0) * 0.25;
        if (S21) mult += (97.0 / 32097.0) * 0.25;
        // Finally, add that attenuated voltage to the main summing junction
        //const double mult = std::sin(k_angle * DEG_TO_RAD);
        const double diff = ladder_amp_voltage * mult;
        junction_voltage += diff;

        return -junction_voltage * msa_gain * CDU_VOLTAGE;
    }

    void Cdu::tick_cmc() {
        // If our ISS timing thread hasn't been created yet, do so.
        // This should only happen once.
        if (!iss_timing_thread.joinable()) {
            iss_timing_thread = std::thread(&Cdu::tick_iss, this);
        }

        prev_state = cur_state;
        ++cur_state;

        const bool squarewave_25_6_kpps = (cur_state & 1);
        const bool squarewave_12_8_kpps = (cur_state & 2);
        const bool squarewave_6_4_kpps = (cur_state & 4);
        const bool pulse_phase1 = (!squarewave_25_6_kpps && !squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase2 = (squarewave_25_6_kpps && !squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase3 = (!squarewave_25_6_kpps && squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase4 = (squarewave_25_6_kpps && squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase4_slow = (squarewave_25_6_kpps && squarewave_12_8_kpps && squarewave_6_4_kpps) && ((cur_state & 1) ^ (prev_state & 1));

        if (pulse_phase1) {
            //std::cout << "phase1" << std::endl;
        }

        if (pulse_phase2) {
            //std::cout << "phase2" << std::endl;
        }

        if (pulse_phase3) {
            //std::cout << "phase3" << std::endl;
        }

        if (pulse_phase4) {
            //std::cout << "phase4" << std::endl;
            refresh_channels();

            // Perform read counter increment/degrement if commanded
            for (size_t i = 0; i < channels.size(); ++i) {
                auto& channel = channels[i];

                // Keep track of the previous read counter state to see if we need to pulse the AGC.
                const uint16_t prev_readcounter_div2 = channel.read_counter / 2;

                if (channel.mode != COARSE_ALIGN && channel.should_count) {
                    channel.read_counter += channel.count_direction == DOWN ? -1 : 1;
                    channel.should_count = false;
                }

                if (channel.count_direction != NONE && channel.read_counter / 2 != prev_readcounter_div2) {
                    Agc::cpu.counters[COUNTER_CDUX + i] = (channel.count_direction == DOWN) ? COUNT_DIRECTION_DOWN : COUNT_DIRECTION_UP;
                }
            }
        }

        if (pulse_phase4_slow) {
            //std::cout << "phase4_slow" << std::endl;
        }
    }

    [[noreturn]] void Cdu::tick_iss() {
        while (true) {
            auto started_at = std::chrono::steady_clock::now();
            auto x = started_at + std::chrono::microseconds(1250);  // 800 Hz

            for (auto& channel : channels) {
                if (channel.count_direction != NONE && channel.count_speed == LOW) {
                    channel.should_count = true;
                }
            }

            // Invert the state of the 800 cps ISS-reference square waves
            iss_phase1_state = !iss_phase1_state;

            //auto ended_at = std::chrono::steady_clock::now();

            std::this_thread::sleep_until(x);
        }
    }

    void Cdu::refresh_channels() {
        for (size_t i = 0; i < channels.size(); ++i) {
            auto& channel = channels[i];

            if (channel.zero_discrete) {
                channel.read_counter = 0;
                continue;
            }

            const double coarse_error = channel.coarse_error();
            // Choose proper fain for the system: 7.5 for ISS, 15.0 for OSS.
            // Per procurement spec 2007238 page 12.
            const double fine_gain = i < 3 ? 7.5 : 15.0;
            const double fine_error = channel.fine_error(fine_gain);

            // Coarse and fine mixing logic
            const bool C1 = std::abs(coarse_error) >= COARSE_C1_TRIGGER;
            const bool F2 = std::abs(fine_error) >= FINE_F2_TRIGGER;
            const bool F1 = std::abs(fine_error) >= FINE_F1_TRIGGER;

            // Set count direction, or none if no error signals exceed thresholds.
            bool count_down = false;
            if (C1) {
                count_down = std::signbit(coarse_error);
                channel.count_direction = count_down ? DOWN : UP;
            } else if (F2 || F1) {
                count_down = std::signbit(fine_error);
                channel.count_direction = count_down ? DOWN : UP;
            } else {
                channel.count_direction = NONE;
            }

            // Based on error signals, set count speed.
            if (C1 || F2) {
                channel.count_speed = HIGH;
                channel.should_count = true;
            } else if (F1) {
                channel.count_speed = LOW;
            }

            if (coarse_error != channel.prev_coarse_error) {
                channel.prev_coarse_error = coarse_error;
                //std::cout << "Coarse error: " << coarse_error / CDU_VOLTAGE * RAD_TO_DEG << std::endl;
            }

            if (fine_error != channel.prev_fine_error) {
                channel.prev_fine_error = fine_error;
                //std::cout << "Fine error: " << fine_error / (CDU_VOLTAGE * fine_gain) * RAD_TO_DEG / 16 << std::endl;
            }
        }
    }

    void Cdu::set_iss_cdu_zero(bool state) {
        for (int c = 0; c < 3; ++c) {
            auto& channel = channels[c];
            channel.zero_discrete = state;
        }
        std::cout << "ISS CDUs zeroed!" << std::endl;
    }

    void Cdu::set_oss_cdu_zero(bool state) {
        for (int c = 3; c < channels.size(); ++c) {
            auto& channel = channels[c];
            channel.zero_discrete = state;
        }
        std::cout << "OSS/Radar CDUs zeroed!" << std::endl;
    }
}
