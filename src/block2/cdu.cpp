#include "cdu.hpp"

#include <cmath>
#include <iostream>

namespace agcplusplus::block2 {
    double CduChannel::sin(const uint8_t resolver_speed = 1) const {
        return std::sin(true_angle * resolver_speed);
    }
    double CduChannel::cos(const uint8_t resolver_speed = 1) const {
        return std::cos(true_angle * resolver_speed);
    }

    void Cdu::tick() {
        prev_state = cur_state;
        ++cur_state;

        bool squarewave_25_6_kpps = (cur_state & 1);
        bool squarewave_12_8_kpps = (cur_state & 2);
        bool pulse_phase1 = (!squarewave_25_6_kpps && !squarewave_12_8_kpps);
        bool pulse_phase2 = (squarewave_25_6_kpps && !squarewave_12_8_kpps);
        bool pulse_phase3 = (!squarewave_25_6_kpps && squarewave_12_8_kpps);
        bool pulse_phase4 = (squarewave_25_6_kpps && squarewave_12_8_kpps);

        if (pulse_phase1) {
            std::cout << "phase1" << std::endl;
        }

        if (pulse_phase2) {
            std::cout << "phase2" << std::endl;
        }

        if (pulse_phase3) {
            std::cout << "phase3" << std::endl;
        }

        if (pulse_phase4) {
            std::cout << "phase4" << std::endl;
        }
    }
}
