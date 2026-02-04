#pragma once
#include <memory>

#include "cdu.hpp"
#include "../common/global_definitions.hpp"

namespace agcplusplus::block2 {
class Imu {
public:
    void gyro_pulse() const;
    void set_gyro_select(int gyro);
    void set_gyro_torque_enable(bool state);

    std::shared_ptr<double> theta_x = std::make_shared<double>(0.0);
    std::shared_ptr<double> theta_y = std::make_shared<double>(0.0);
    std::shared_ptr<double> theta_z = std::make_shared<double>(0.0);

private:
    constexpr static double GYRO_PULSE_AMOUNT = 360.0 / std::pow(2, 21) * DEG_TO_RAD;    // 0.617981 arc-seconds per pulse
    bool gyro_torque_enable = false;
    int gyro_select = 0;
};
}
