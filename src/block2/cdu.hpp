#pragma once

#include <array>
#include <cstdint>
#include <thread>

#include "block2defs.hpp"

namespace agcplusplus::block2 {
class CduChannel {
public:
    double theta = 0.0 * DEG_TO_RAD; // Radians
    uint16_t read_counter = 0;  // Multiplied by 20 arc-seconds to get degrees

    [[nodiscard]] double coarse_error() const;
    [[nodiscard]] double fine_error() const;
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
