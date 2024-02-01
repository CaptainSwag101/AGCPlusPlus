#pragma once

#include <array>
#include <cmath>
#include <cstdint>

namespace agcplusplus::block2 {
class CduChannel {
public:
    double theta = 0.0;
    uint16_t read_counter = 00004400;

    [[nodiscard]] double sin(uint8_t resolver_speed) const;
    [[nodiscard]] double cos(uint8_t resolver_speed) const;
    [[nodiscard]] double compute_angle_error() const;

private:
};

class Cdu {
public:
    uint64_t cur_state = UINT64_MAX;
    uint64_t prev_state = 0;

    void tick();

private:
    std::array<CduChannel, 5> channels{};
};
}
