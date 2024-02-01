#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <thread>

#include "block2defs.hpp"

namespace agcplusplus::block2 {
constexpr static uint8_t RESOLVER_1X = 1;
constexpr static uint8_t RESOLVER_16X = 16;
constexpr static uint8_t RESOLVER_64X = 64;

class CduChannel {
public:
    double theta = 10.0 * DEG_TO_RAD; // Radians
    uint16_t read_counter = 0;  // Multiplied by 20 arc-seconds to get degrees
    double coarse_error = 0.0;  // Degrees
    double fine_error = 0.0;    // Degrees

    [[nodiscard]] double sin_theta(uint8_t resolver_speed) const;
    [[nodiscard]] double cos_theta(uint8_t resolver_speed) const;
    [[nodiscard]] double compute_angle_error(uint8_t resolver_speed) const;
    void refresh();
};

class Cdu {
public:
    uint64_t cur_state = UINT64_MAX;
    uint64_t prev_state = 0;

    void tick_cmc();
    [[noreturn]] void tick_iss();

private:
    std::array<CduChannel, 1> channels{};
    std::thread iss_timing_thread;
};
}
