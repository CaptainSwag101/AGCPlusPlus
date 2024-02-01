#include "cdu.hpp"

#include "block2defs.hpp"
#include <cmath>
#include <iostream>

namespace agcplusplus::block2 {
    double CduChannel::sin_theta(const uint8_t resolver_speed) const {
        const double result = std::sin(theta * resolver_speed);
        return result;
    }

    double CduChannel::cos_theta(const uint8_t resolver_speed) const {
        const double result = std::cos(theta * resolver_speed);
        return result;
    }

    double CduChannel::compute_angle_error(const uint8_t resolver_speed) const {
        const double psi = TWENTY_ARCSECONDS * read_counter * DEG_TO_RAD;

        // We can do it in two steps...
        //const double step1 = sin_theta(resolver_speed) * std::cos(psi);
        //const double step2 = cos_theta(resolver_speed) * std::sin(psi);

        // +/- sin(theta) cos(psi) -/+ cos(theta) sin(psi)
        //return step1 + (-1.0 * step2);

        // ...Or one step.
        return std::sin((theta * resolver_speed) - (psi * resolver_speed));
    }

    void Cdu::tick_cmc() {
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
                double coarse_error = channel.compute_angle_error(RESOLVER_1X) * RAD_TO_DEG;
                double fine_error = channel.compute_angle_error(RESOLVER_16X) * RAD_TO_DEG / 16;

                // Coarse and fine mixing logic
                const bool C1 = std::abs(coarse_error) >= 7.0;
                // Yes this is intentionally still using coarse error, with fine error I can't get a good value
                const bool F2 = std::abs(fine_error) >= 0.1;

                bool count_down = false;
                if (C1) {
                    count_down = std::signbit(coarse_error);
                } else if (F2) {
                    count_down = std::signbit(fine_error);
                }

                std::cout << coarse_error << std::endl;
                std::cout << fine_error << std::endl;

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
            auto x = started_at + std::chrono::seconds(1 / 800);

            for (auto& channel : channels) {
                const double coarse_error = channel.compute_angle_error(RESOLVER_1X) * RAD_TO_DEG;
                const double fine_error = channel.compute_angle_error(RESOLVER_16X) * RAD_TO_DEG / 16;

                // Coarse and fine mixing logic
                const bool F1 = std::abs(fine_error) >= TWENTY_ARCSECONDS && std::abs(fine_error) < 0.1;

                std::cout << coarse_error << std::endl;
                std::cout << fine_error << std::endl;

                if (F1) {
                    const bool count_down = std::signbit(fine_error);
                    channel.read_counter += (!count_down) ? 1 : -1;
                }
            }

            //auto ended_at = std::chrono::steady_clock::now();

            std::this_thread::sleep_until(x);
        }
    }
}
