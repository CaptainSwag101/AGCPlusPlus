#include "cdu.hpp"

#include "block2defs.hpp"
#include <cmath>
#include <iostream>

namespace agcplusplus::block2 {
    double CduChannel::sin(const uint8_t resolver_speed = 1) const {
        return std::sin(theta * resolver_speed);
    }

    double CduChannel::cos(const uint8_t resolver_speed = 1) const {
        return std::cos(theta * resolver_speed);
    }

    double CduChannel::compute_angle_error() const {
        const double psi = TWENTY_ARCSECONDS * read_counter;

        // We could do it in two steps...
        //const double step1 = std::sin(theta * DEG_TO_RAD) * std::cos(psi * DEG_TO_RAD);
        //const double step2 = std::cos(theta * DEG_TO_RAD) * std::sin(psi * DEG_TO_RAD);

        // +/- sin(theta) cos(psi) -/+ cos(theta) sin(psi)
        //return (step1 + (std::signbit(step1) * -1.0) * step2) * RAD_TO_DEG;

        // ... or do it all in one step
        return std::sin((theta - psi) * DEG_TO_RAD) * RAD_TO_DEG;
    }

    void Cdu::tick() {
        prev_state = cur_state;
        ++cur_state;

        bool squarewave_25_6_kpps = (cur_state & 1);
        bool squarewave_12_8_kpps = (cur_state & 2);
        bool squarewave_6_4_kpps = (cur_state & 4);
        bool pulse_phase1 = (!squarewave_25_6_kpps && !squarewave_12_8_kpps) && ((cur_state & 1) ^ (prev_state & 1));
        bool pulse_phase2 = (squarewave_25_6_kpps && !squarewave_12_8_kpps) && ((cur_state & 1) ^ (prev_state & 1));
        bool pulse_phase3 = (!squarewave_25_6_kpps && squarewave_12_8_kpps) && ((cur_state & 1) ^ (prev_state & 1));
        bool pulse_phase4 = (squarewave_25_6_kpps && squarewave_12_8_kpps) && ((cur_state & 1) ^ (prev_state & 1));
        bool pulse_phase4_slow = (squarewave_25_6_kpps && squarewave_12_8_kpps && squarewave_6_4_kpps) && ((cur_state & 1) ^ (prev_state & 1));

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
        }

        if (pulse_phase4_slow) {
            //std::cout << "phase4_slow" << std::endl;
        }


        for (auto& channel : channels) {
            const double angle_error = channel.compute_angle_error();
            std::cout << angle_error << std::endl;
        }
    }
}
