#include "cdu.hpp"

#include "block2defs.hpp"
#include <cmath>
#include <iostream>

namespace agcplusplus::block2 {
    double CduChannel::coarse_error() const {
        return 0.0;
    }

    double CduChannel::fine_error() const {
        return 0.0;
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
                const double coarse_error = channel.coarse_error();
                const double fine_error = channel.fine_error();

                // Coarse and fine mixing logic
                const bool C1 = std::abs(coarse_error) >= 7.0;
                const bool F2 = std::abs(fine_error) >= 0.1;

                bool count_down = false;
                if (C1) {
                    count_down = std::signbit(coarse_error);
                } else if (F2) {
                    count_down = std::signbit(fine_error);
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
                const double coarse_error = channel.coarse_error();
                const double fine_error = channel.fine_error();

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

            std::this_thread::sleep_until(x);
        }
    }
}
