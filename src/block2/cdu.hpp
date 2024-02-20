#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <thread>

#include "block2defs.hpp"

namespace agcplusplus::block2 {

// These resistors have the cos- or sin-modulated 5V RMS voltage from the resolver.
constexpr double COARSE_S1_RESISTOR = std::cos(22.5 * DEG_TO_RAD);
constexpr double COARSE_S2_RESISTOR = std::cos(67.5 * DEG_TO_RAD);
constexpr double COARSE_S3_RESISTOR = std::cos(22.5 * DEG_TO_RAD);
constexpr double COARSE_S4_RESISTOR = std::cos(67.5 * DEG_TO_RAD);
constexpr double COARSE_S5_RESISTOR = std::sin(22.5 * DEG_TO_RAD);
constexpr double COARSE_S6_RESISTOR = std::sin(67.5 * DEG_TO_RAD);
constexpr double COARSE_S7_RESISTOR = std::sin(22.5 * DEG_TO_RAD);
constexpr double COARSE_S8_RESISTOR = std::sin(67.5 * DEG_TO_RAD);
// These resistors have the whole 5V RMS voltage from the ISS reference.
constexpr double COARSE_S9_RESISTOR = std::sin(22.5 * DEG_TO_RAD);
constexpr double COARSE_S10_RESISTOR = std::sin(11.25 * DEG_TO_RAD);
constexpr double COARSE_S11_RESISTOR = std::sin(5.6 * DEG_TO_RAD);
constexpr double COARSE_S12_RESISTOR = std::sin(2.8 * DEG_TO_RAD);
// The coarse system transformers bring 28V RMS down to 5V RMS.
constexpr double COARSE_VOLTAGE = 5.0;
// This is the logic for closing any of the coarse switches S1-S12.
// There is a value and mask, the mask being applied first and then the value checked.
// There may be more than one value per switch.
constexpr uint16_t DC1_VALUE1 = 0 | BITMASK_14 | BITMASK_13;
constexpr uint16_t DC1_VALUE2 = ~DC1_VALUE1;
constexpr uint16_t DC1_MASK = BITMASK_15 | BITMASK_14 | BITMASK_13;
constexpr uint16_t DC2_VALUE1 = 0 | BITMASK_14 | 0;
constexpr uint16_t DC2_VALUE2 = ~DC2_VALUE1;
constexpr uint16_t DC2_MASK = DC1_MASK;
constexpr uint16_t DC3_VALUE1 = BITMASK_15 | BITMASK_14 | BITMASK_13;
constexpr uint16_t DC3_VALUE2 = ~DC3_VALUE1;
constexpr uint16_t DC3_MASK = DC1_MASK;
constexpr uint16_t DC4_VALUE1 = 0 | 0 | BITMASK_13;
constexpr uint16_t DC4_VALUE2 = ~DC4_VALUE1;
constexpr uint16_t DC4_MASK = DC1_MASK;
constexpr uint16_t DC5_VALUE1 = 0 | BITMASK_14 | BITMASK_13;
constexpr uint16_t DC5_VALUE2 = 0 | 0 | 0;
constexpr uint16_t DC5_MASK = DC1_MASK;
constexpr uint16_t DC6_VALUE1 = 0 | 0 | BITMASK_13;
constexpr uint16_t DC6_VALUE2 = 0 | BITMASK_14 | 0;
constexpr uint16_t DC6_MASK = DC1_MASK;
constexpr uint16_t DC7_VALUE1 = BITMASK_15 | BITMASK_14 | BITMASK_13;
constexpr uint16_t DC7_VALUE2 = BITMASK_15 | 0 | 0;
constexpr uint16_t DC7_MASK = DC1_MASK;
constexpr uint16_t DC8_VALUE1 = BITMASK_15 | 0 | BITMASK_13;
constexpr uint16_t DC8_VALUE2 = BITMASK_15 | BITMASK_14 | 0;
constexpr uint16_t DC8_MASK = DC1_MASK;
constexpr uint16_t DC9_VALUE = 0;
constexpr uint16_t DC9_MASK = BITMASK_12;
constexpr uint16_t DC10_VALUE = BITMASK_11;
constexpr uint16_t DC10_MASK = BITMASK_11;
constexpr uint16_t DC11_VALUE = BITMASK_10;
constexpr uint16_t DC11_MASK = BITMASK_10;
constexpr uint16_t DC12_VALUE = BITMASK_9;
constexpr uint16_t DC12_MASK = BITMASK_9;

class CduChannel {
public:
    double theta = 225.0 * DEG_TO_RAD; // Radians
    uint16_t read_counter = static_cast<uint16_t>(225.0 / TWENTY_ARCSECONDS);  // Multiplied by 20 arc-seconds to get degrees

    [[nodiscard]] double coarse_error() const;
    [[nodiscard]] double fine_error() const;
};

class Cdu {
public:
    uint64_t cur_state = UINT64_MAX;
    uint64_t prev_state = 0;
    bool iss_inphase_sign = false;
    bool iss_outphase_sign = !iss_inphase_sign;

    void tick_cmc();
    [[noreturn]] void tick_iss();

private:
    std::array<CduChannel, 1> channels{};
    std::thread iss_timing_thread;
};
}
