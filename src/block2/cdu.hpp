#pragma once

#include <array>
#include <cstdint>

namespace agcplusplus::block2 {
class CduChannel {
public:
    double true_angle = 0.0;
    uint16_t read_counter = 0;

    [[nodiscard]] double sin(uint8_t resolver_speed) const;
    [[nodiscard]] double cos(uint8_t resolver_speed) const;
};

class Cdu {
public:
    uint64_t cur_state = 0;
    uint64_t prev_state = 0;

    void tick();

private:
    std::array<CduChannel, 5> channels{};
};
}
