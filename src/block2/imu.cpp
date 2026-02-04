#include "imu.hpp"
#include "agc.hpp"

namespace agcplusplus::block2 {
void Imu::gyro_pulse() const {
    const int gyro_number = gyro_select & 3;
    const double torque_value = GYRO_PULSE_AMOUNT *  ((gyro_select & 4) > 0 ? -1.0 : 1.0);
    switch (gyro_number) {
        case 1:
            *theta_x += torque_value;
            break;
        case 2:
            *theta_y += torque_value;
            break;
        case 3:
            *theta_z += torque_value;
            break;
        default:
            break;
    }
}

void Imu::set_gyro_select(int gyro) {
    gyro_select = gyro;
    Agc::log_stream << "Gyro select = " << gyro << std::endl;
}

void Imu::set_gyro_torque_enable(const bool state) {
    gyro_torque_enable = state;
    Agc::log_stream << "Gyro torque enable = " << state << std::endl;
}

}
