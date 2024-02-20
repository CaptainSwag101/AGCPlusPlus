#include "cdu.hpp"

#include <cmath>
#include <iostream>

namespace agcplusplus::block2 {
    double CduChannel::coarse_error() const {
        const double cos_voltage = std::cos(theta) * COARSE_VOLTAGE;
        const double sin_voltage = std::sin(theta) * COARSE_VOLTAGE;

        // Determine the output at the op-amp by summing up the coarse system switches,
        // per the DC1-DC12 logic dependent on the set bits of the read counter.
        double amplifier_output = 0.0;

        // Figure out what appropriate conditions for any of the switches have been met.
        // Sine section.
        if ((read_counter & DC1_MASK) == (DC1_VALUE1 & DC1_MASK) ||
            (read_counter & DC1_MASK) == (DC1_VALUE2 & DC1_MASK)) {
            amplifier_output += -sin_voltage * COARSE_S1_RESISTOR;
        }
        if ((read_counter & DC2_MASK) == (DC2_VALUE1 & DC2_MASK) ||
            (read_counter & DC2_MASK) == (DC2_VALUE2 & DC2_MASK)) {
            amplifier_output += -sin_voltage * COARSE_S2_RESISTOR;
        }
        if ((read_counter & DC3_MASK) == (DC3_VALUE1 & DC3_MASK) ||
            (read_counter & DC3_MASK) == (DC3_VALUE2 & DC3_MASK)) {
            amplifier_output += sin_voltage * COARSE_S3_RESISTOR;
        }
        if ((read_counter & DC4_MASK) == (DC4_VALUE1 & DC4_MASK) ||
            (read_counter & DC4_MASK) == (DC4_VALUE2 & DC4_MASK)) {
            amplifier_output += sin_voltage * COARSE_S4_RESISTOR;
        }
        // Cosine section.
        if ((read_counter & DC5_MASK) == (DC5_VALUE1 & DC5_MASK) ||
            (read_counter & DC5_MASK) == (DC5_VALUE2 & DC5_MASK)) {
            amplifier_output += -cos_voltage * COARSE_S5_RESISTOR;
        }
        if ((read_counter & DC6_MASK) == (DC6_VALUE1 & DC6_MASK) ||
            (read_counter & DC6_MASK) == (DC6_VALUE2 & DC6_MASK)) {
            amplifier_output += -cos_voltage * COARSE_S6_RESISTOR;
        }
        if ((read_counter & DC7_MASK) == (DC7_VALUE1 & DC7_MASK) ||
            (read_counter & DC7_MASK) == (DC7_VALUE2 & DC7_MASK)) {
            amplifier_output += cos_voltage * COARSE_S7_RESISTOR;
        }
        if ((read_counter & DC8_MASK) == (DC8_VALUE1 & DC8_MASK) ||
            (read_counter & DC8_MASK) == (DC8_VALUE2 & DC8_MASK)) {
            amplifier_output += cos_voltage * COARSE_S8_RESISTOR;
        }
        // Coarse-fine common switches.
        if ((read_counter & DC9_MASK) == (DC9_VALUE & DC9_MASK)) {
            amplifier_output += COARSE_VOLTAGE * COARSE_S9_RESISTOR;
        }
        if ((read_counter & DC10_MASK) == (DC10_VALUE & DC10_MASK)) {
            amplifier_output += COARSE_VOLTAGE * COARSE_S10_RESISTOR;
        }
        if ((read_counter & DC11_MASK) == (DC11_VALUE & DC11_MASK)) {
            amplifier_output += COARSE_VOLTAGE * COARSE_S11_RESISTOR;
        }
        if ((read_counter & DC12_MASK) == (DC12_VALUE & DC12_MASK)) {
            amplifier_output += COARSE_VOLTAGE * COARSE_S12_RESISTOR;
        }

        return amplifier_output / COARSE_VOLTAGE;
    }

    double CduChannel::fine_error() const {
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
        const bool pulse_phase1 = (!squarewave_25_6_kpps && !squarewave_12_8_kpps);
        const bool pulse_phase2 = (squarewave_25_6_kpps && !squarewave_12_8_kpps);
        const bool pulse_phase3 = (!squarewave_25_6_kpps && squarewave_12_8_kpps);
        const bool pulse_phase4 = (squarewave_25_6_kpps && squarewave_12_8_kpps);
        const bool pulse_phase4_slow = (squarewave_25_6_kpps && squarewave_12_8_kpps && squarewave_6_4_kpps) && ((cur_state & 1) ^ (prev_state & 1));

        if (pulse_phase1) {
            //std::cout << "phase1" << std::endl;
            for (auto& channel : channels) {
                static double prev_coarse_error = 0.0;

                const double coarse_error = channel.coarse_error() * RAD_TO_DEG;
                const double fine_error = channel.fine_error() * RAD_TO_DEG;

                // Coarse and fine mixing logic
                const bool C1 = std::abs(coarse_error) >= 7.0;
                const bool F2 = std::abs(fine_error) >= 0.1;

                bool count_down = false;
                if (C1) {
                    count_down = std::signbit(coarse_error);
                } else if (F2) {
                    count_down = std::signbit(fine_error);
                }

                if (coarse_error != prev_coarse_error) {
                    prev_coarse_error = coarse_error;
                    std::cout << "Coarse error: " << coarse_error << std::endl;
                }
                //std::cout << coarse_error << std::endl;
                //std::cout << fine_error << std::endl;

                if (C1 || F2) {
                    channel.read_counter += (!count_down) ? 1 : -1;
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

            for (auto& channel : channels) {
                const double coarse_error = channel.coarse_error() * RAD_TO_DEG;
                const double fine_error = channel.fine_error() * RAD_TO_DEG;

                // Coarse and fine mixing logic
                const bool C1 = std::abs(coarse_error) >= 7.0;
                const bool F2 = std::abs(fine_error) >= 0.1;
                const bool F1 = std::abs(fine_error) >= TWENTY_ARCSECONDS && std::abs(fine_error) < 0.1;

                if (F1 && !(C1 || F2)) {
                    const bool count_down = std::signbit(fine_error);
                    channel.read_counter += (!count_down) ? 1 : -1;
                }

                if (!F1 && !(C1 || F2) && std::abs(fine_error) < TWENTY_ARCSECONDS && !converged) {
                    const double psi = TWENTY_ARCSECONDS * channel.read_counter;
                    std::cout << "Converged. True Angle: " << channel.theta * RAD_TO_DEG << ", Computed Angle: " << psi << std::endl;
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
