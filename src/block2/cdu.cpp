#include "cdu.hpp"

#include <cmath>
#include <iostream>

#include "agc.hpp"

namespace agcplusplus::block2 {
    CduChannel::CduChannel(const std::string& name) {
        channel_name = name;
        log_csv = std::ofstream("log_" + name + ".csv");
        log_csv << "Theta,Psi,CoarseError,FineError,ErrorCounter,RC_Count,EC_Count\n";
    }

    double CduChannel::get_coarse_error() const {
        const double cos_voltage = std::cos(theta) * COARSE_VOLTAGE;
        const double sin_voltage = std::sin(theta) * COARSE_VOLTAGE;

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
            amplifier_output += COARSE_VOLTAGE * COARSE_S9_RESISTOR;
        }
        if ((read_counter & COARSE_S10_MASK) == (COARSE_S10_VALUE & COARSE_S10_MASK)) {
            amplifier_output += -COARSE_VOLTAGE * COARSE_S10_RESISTOR;
        }
        if ((read_counter & COARSE_S11_MASK) == (COARSE_S11_VALUE & COARSE_S11_MASK)) {
            amplifier_output += -COARSE_VOLTAGE * COARSE_S11_RESISTOR;
        }
        if ((read_counter & COARSE_S12_MASK) == (COARSE_S12_VALUE & COARSE_S12_MASK)) {
            amplifier_output += -COARSE_VOLTAGE * COARSE_S12_RESISTOR;
        }

        return amplifier_output;
    }

    double CduChannel::get_fine_error(double msa_gain) const {
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

        return -junction_voltage * msa_gain * FINE_VOLTAGE;
    }

    void Cdu::tick_cmc() {
        // If our ISS timing thread hasn't been created yet, do so.
        // This should only happen once.
        if (!iss_timing_thread.joinable()) {
            iss_timing_thread = std::thread(&Cdu::tick_iss, this);
        }

        // Tick our binary counters for timing and phase control.
        prev_state = cur_state;
        ++cur_state;

        //HACK: Lightning strike at 60 seconds, set read counter bit 14
        /*if (cur_state == 25600 * 60) {
            std::cout << "LIGHTNING STRIKE!" << std::endl;

            for (size_t c = 0; c < 3; ++c) {
                channels[c].read_counter |= B14;
            }
        }*/

        const bool squarewave_25_6_kpps = (cur_state & 1);
        const bool squarewave_12_8_kpps = (cur_state & 2);
        const bool squarewave_6_4_kpps = (cur_state & 4);
        const bool pulse_phase1 = (!squarewave_25_6_kpps && !squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase2 = (squarewave_25_6_kpps && !squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase3 = (!squarewave_25_6_kpps && squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase4 = (squarewave_25_6_kpps && squarewave_12_8_kpps) && (prev_state != cur_state);
        const bool pulse_phase4_slow = (squarewave_25_6_kpps && squarewave_12_8_kpps && squarewave_6_4_kpps) && ((cur_state & 1) ^ (prev_state & 1));

        if (pulse_phase1) {
            //Agc::log_stream << "phase1" << std::endl;
        }

        if (pulse_phase2) {
            //Agc::log_stream << "phase2" << std::endl;

            // Determine error and up/down count direction for each channel.
            refresh_channels();
        }

        if (pulse_phase3) {
            //Agc::log_stream << "phase3" << std::endl;
        }

        if (pulse_phase4) {
            //Agc::log_stream << "phase4" << std::endl;

            // Pulse at 12.8 kpps if not in coarse align.
            for (size_t c = 0; c < channels.size(); ++c) {
                auto& channel = channels[c];

                const double theta_degrees = channel.theta * RAD_TO_DEG;
                const double psi_degrees = channel.read_counter * TWENTY_ARCSECONDS;
                channel.log_csv << theta_degrees << ',';
                channel.log_csv << psi_degrees << ',';
                channel.log_csv << channel.get_coarse_error() << ',';
                channel.log_csv << channel.get_fine_error(1.0) << ',';
                channel.log_csv << channel.error_counter << ',';
                channel.log_csv << (int)channel.should_count << ',';
                channel.log_csv << (int)(channel.error_counter_direction != NONE) << '\n';

                if (!channels[c].coarse_align) {
                    pulse_channel(c);
                }
            }
        }

        if (pulse_phase4_slow) {
            //Agc::log_stream << "phase4_slow" << std::endl;

            // Pulse at 6.4 kpps if in coarse align
            for (size_t c = 0; c < channels.size(); ++c) {
                if (channels[c].coarse_align) {
                    pulse_channel(c);
                }
            }
        }
    }

    // This thread should do as little as possible logically, hopefully just
    // setting booleans and such and keeping track of interrogate pulses if I need them.
    [[noreturn]] void Cdu::tick_iss() {
        while (true) {
            auto started_at = std::chrono::steady_clock::now();
            auto x = started_at + std::chrono::microseconds(1250);  // 800 Hz

            for (auto& channel : channels) {
                if (channel.read_counter_direction != NONE && channel.count_speed == LOW) {
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
        for (size_t channel_num = 0; channel_num < channels.size(); ++channel_num) {
            auto& channel = channels[channel_num];

            /*
             * The majority of the functionality below simulates the behavior of
             * the Error Counter & Logic Module related to the read counter.
             */

            // The CDU ZERO discrete resets the read counter and prevents counts.
            if (channel.zero_discrete) {
                channel.read_counter = 0;
                continue;
            }

            const double coarse_error = channel.get_coarse_error();
            // Choose proper gain for the system: 7.5 for ISS, 15.0 for OSS.
            // Per procurement spec 2007238 page 12.
            const double fine_gain = channel_num < 3 ? 7.5 : 15.0;
            const double fine_error = channel.get_fine_error(fine_gain);

            // Coarse and fine mixing logic
            const bool C1 = std::abs(coarse_error) >= COARSE_C1_TRIGGER;
            const bool F2 = std::abs(fine_error) >= FINE_F2_TRIGGER;
            const bool F1 = std::abs(fine_error) >= FINE_F1_TRIGGER;

            // Set count direction, or none if no error signals exceed thresholds.
            bool count_down = false;
            if (C1) {
                count_down = std::signbit(coarse_error);
                channel.read_counter_direction = count_down ? DOWN : UP;
            } else if (F2 || F1) {
                count_down = std::signbit(fine_error);
                channel.read_counter_direction = count_down ? DOWN : UP;
            } else {
                channel.read_counter_direction = NONE;
            }

            // Based on error signals, set count speed.
            if (C1 || F2) {
                channel.count_speed = HIGH;
                channel.should_count = true;
            } else if (F1) {
                channel.count_speed = LOW;
            }

            // These are emulator-related values which I use for printing out the errors as they change.
            if (coarse_error != channel.prev_coarse_error) {
                channel.prev_coarse_error = coarse_error;
                //Agc::log_stream << "Coarse error: " << coarse_error / CDU_VOLTAGE * RAD_TO_DEG << std::endl;
            }

            if (fine_error != channel.prev_fine_error) {
                channel.prev_fine_error = fine_error;
                //Agc::log_stream << "Fine error: " << fine_error / (CDU_VOLTAGE * fine_gain) * RAD_TO_DEG / 16 << std::endl;
            }
        }
    }

    void Cdu::pulse_channel(const size_t channel_index) {
        // Perform read counter increment/degrement if commanded
        auto& channel = channels[channel_index];

        // Keep track of the previous read counter state to see if we need to pulse the AGC or error counter.
        const uint16_t prev_readcounter_div2 = channel.read_counter / 2;
        const uint16_t prev_readcounter_div4 = channel.read_counter / 8;

        // Send pulse train to AGC, and count down error counter.
        // Don't pulse the read counter if we just got an error counter pulse from the AGC.
        if (channel.should_count && (!channel.error_counter_enable || channel.error_counter_direction == NONE)) {
            channel.read_counter += channel.read_counter_direction == DOWN ? -1 : 1;

            const uint16_t cur_readcounter_div2 = channel.read_counter / 2; // Check for bit 0 overflow (in bit 1)
            const uint16_t cur_readcounter_div4 = channel.read_counter / 8; // Check for bit 2 overflow (in bit 2)

            if (cur_readcounter_div2 != prev_readcounter_div2)
                Agc::cpu.counters[COUNTER_CDUX + channel_index] = (channel.read_counter_direction == DOWN) ? COUNT_DIRECTION_DOWN : COUNT_DIRECTION_UP;

            // Error Counter countdown is either 3200 cps or 800 cps depending on error signals F2/C1 vs. F1.
            if (cur_readcounter_div4 != prev_readcounter_div4 && channel.error_counter_enable) {
                channel.error_counter -= 1;
                if (channel.error_counter < 0) channel.error_counter = 0;
            }

            channel.should_count = false;
        }

        // AGC -> error counter logic
        if (channel.error_counter_enable && channel.error_counter_direction != NONE) {
            // Polarity correction logic; the computer may not count down through zero
            if (channel.error_counter == 0 && channel.error_counter_direction == DOWN) {
                channel.error_counter_polarity_invert = !channel.error_counter_polarity_invert;
            }

            CDU_COUNT_DIRECTION corrected_direction = channel.error_counter_direction;
            if (channel.error_counter_polarity_invert) {
                // Invert the direction
                corrected_direction = corrected_direction == DOWN ? UP : DOWN;
            }

            // Pulse the error counter
            channel.error_counter += corrected_direction == DOWN ? -1 : 1;
            if (channel.error_counter > 384) {
                std::cerr << "Error counter saturated! This could be a problem." << std::endl;
                channel.error_counter = 384;
            }
        }
        channel.error_counter_direction = NONE;

        // Coarse Align and DAC
        if (channel.coarse_align && channel.error_counter_enable) {
            // DAC and coarse align mixing amplifier
            const double v_dac = channel.error_counter * 0.0132 * (channel.error_counter_polarity_invert ? -1.0 : 1.0);    // 13.2 mV rms per bit
            const double v_dac_clamped = std::clamp(v_dac, -0.5, 0.5);  // Diode limited to 0.5 volts?
            const double fine_error = channel.get_fine_error(1.0);
            const double v_ca = (v_dac_clamped * 0.265) + (fine_error * 0.828);     // Mixing ratio is 3:1 in favor of fine error
            const double v_ca_clamped = std::clamp(v_ca, -0.105, 0.105);    // 0.105 volts is enough to drive the gimbal torque amplifier at its max

            if (std::abs(v_ca_clamped) > 5E-4) {
                const double theta_degrees = channel.theta * RAD_TO_DEG;
                channel.theta += (TWENTY_ARCSECONDS * 8.0) * DEG_TO_RAD * (v_ca_clamped / 0.105);
                if (channel.theta < 0.0)
                    channel.theta = (360.0 * DEG_TO_RAD) + channel.theta;
                if (channel.theta > (360.0 * DEG_TO_RAD))
                    channel.theta = channel.theta - (360.0 * DEG_TO_RAD);
            }
        }
    }

    void Cdu::set_iss_coarse_align(const bool state) {
        for (int c = 0; c < 3; ++c) {
            auto& channel = channels[c];
            channel.coarse_align = state;
        }
        //Agc::log_stream << "ISS coarse align = " << state << std::endl;
    }

    void Cdu::set_iss_error_counter_enable(const bool state) {
        for (int c = 0; c < 3; ++c) {
            auto& channel = channels[c];
            channel.error_counter_enable = state;

            if (state == false) {
                channel.error_counter = 0;
            }
        }
        //Agc::log_stream << "ISS error counter enable = " << state << std::endl;
    }

    void Cdu::set_oss_coarse_align(const bool state) {
        for (int c = 3; c < channels.size(); ++c) {
            auto& channel = channels[c];
            channel.coarse_align = state;
        }
        //Agc::log_stream << "OSS/Radar coarse align = " << state << std::endl;
    }

    void Cdu::set_oss_error_counter_enable(const bool state) {
        for (int c = 3; c < channels.size(); ++c) {
            auto& channel = channels[c];
            channel.error_counter_enable = state;

            if (state == false) {
                channel.error_counter = 0;
            }
        }
        //Agc::log_stream << "OSS/Radar error counter enable = " << state << std::endl;
    }

    void Cdu::set_iss_cdu_zero(const bool state) {
        for (int c = 0; c < 3; ++c) {
            auto& channel = channels[c];
            channel.zero_discrete = state;
        }
        /* if (state)
            Agc::log_stream << "ISS CDUs zeroed!" << std::endl; */
    }

    void Cdu::set_oss_cdu_zero(const bool state) {
        for (int c = 3; c < channels.size(); ++c) {
            auto& channel = channels[c];
            channel.zero_discrete = state;
        }
        /* if (state)
            Agc::log_stream << "OSS/Radar CDUs zeroed!" << std::endl; */
    }

    void Cdu::count_channel_error_counter(const size_t channel_index, const CDU_COUNT_DIRECTION direction) {
        channels[channel_index].error_counter_direction = direction;
    }
}
