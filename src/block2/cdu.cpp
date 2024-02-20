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

    double CduChannel::fine_error() const {
        // 16X resolver speed
        const double cos_voltage = std::cos(16.0 * theta) * CDU_VOLTAGE;
        const double sin_voltage = std::sin(16.0 * theta) * CDU_VOLTAGE;



        return 0.0;
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
            for (size_t i = 0; i < channels.size(); ++i) {
                auto& channel = channels[i];

                static double prev_coarse_error = 0.0;

                const double coarse_error = channel.coarse_error();
                const double fine_error = channel.fine_error();

                // Coarse and fine mixing logic
                const bool C1 = std::abs(coarse_error) >= COARSE_C1_TRIGGER;
                const bool F2 = std::abs(fine_error) >= FINE_F2_TRIGGER;
                //const bool F1 = std::abs(fine_error) >= FINE_F1_TRIGGER;

                bool count_down = false;
                if (C1) {
                    count_down = std::signbit(coarse_error);
                } else if (F2) {
                    count_down = std::signbit(fine_error);
                }

                if (coarse_error != prev_coarse_error) {
                    prev_coarse_error = coarse_error;
                    std::cout << "Coarse error: " << coarse_error / CDU_VOLTAGE * RAD_TO_DEG << std::endl;
                }

                if (C1 || F2) {
                    // Keep track of the previous read counter state to see if we need to pulse the AGC.
                    const uint16_t prev_div2_read_counter = channel.read_counter / 2;

                    channel.read_counter += (!count_down) ? 1 : -1;

                    const uint16_t div2_read_counter = channel.read_counter / 2;
                    if (prev_div2_read_counter != div2_read_counter) {
                        //std::cout << "Pulsed CMC!" << std::endl;
                        Agc::cpu.counters[COUNTER_CDUX + i] |= (count_down ? COUNT_DIRECTION_DOWN : COUNT_DIRECTION_UP);
                    }
                }
            }
        }

        if (pulse_phase2) {
            //std::cout << "phase2" << std::endl;
        }

        if (pulse_phase3) {
            //std::cout << "phase3" << std::endl;
        }

        if (pulse_phase4) {
            //std::cout << "phase4" << std::endl;
        }

        if (pulse_phase4_slow) {
            //std::cout << "phase4_slow" << std::endl;
        }
    }

    [[noreturn]] void Cdu::tick_iss() {
        while (true) {
            auto started_at = std::chrono::steady_clock::now();
            auto x = started_at + std::chrono::microseconds(1250);  // 800 Hz
            static bool converged = false;

            for (size_t i = 0; i < channels.size(); ++i) {
                auto& channel = channels[i];

                const double coarse_error = channel.coarse_error();
                const double fine_error = channel.fine_error();

                // Coarse and fine mixing logic
                const bool C1 = std::abs(coarse_error) >= COARSE_C1_TRIGGER;
                const bool F2 = std::abs(fine_error) >= FINE_F2_TRIGGER;
                const bool F1 = std::abs(fine_error) >= FINE_F1_TRIGGER;

                if (F1 && !(C1 || F2)) {
                    const bool count_down = std::signbit(fine_error);

                    // Keep track of the previous read counter state to see if we need to pulse the AGC.
                    const uint16_t prev_div2_read_counter = channel.read_counter / 2;

                    channel.read_counter += (!count_down) ? 1 : -1;

                    const uint16_t div2_read_counter = channel.read_counter / 2;
                    if (prev_div2_read_counter != div2_read_counter) {
                        Agc::cpu.counters[COUNTER_CDUX + i] |= (count_down ? COUNT_DIRECTION_DOWN : COUNT_DIRECTION_UP);
                    }
                }

                if (!F1 && !(C1 || F2) && !converged) {
                    const double psi = TWENTY_ARCSECONDS * channel.read_counter;
                    std::cout << "Coarse align converged. True Angle: " << channel.theta * RAD_TO_DEG << ", Computed Angle: " << psi << std::endl;
                    converged = true;
                }
            }

            //auto ended_at = std::chrono::steady_clock::now();

            // Invert the state of the 800 cps ISS-reference square waves
            iss_inphase_sign = !iss_inphase_sign;
            iss_outphase_sign = !iss_outphase_sign;

            std::this_thread::sleep_until(x);
        }
    }
}
