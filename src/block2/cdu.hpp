#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <thread>

namespace agcplusplus::block2 {

constexpr static double TWENTY_ARCSECONDS = 180 / std::pow(2, 15);
constexpr static double DEG_TO_RAD = M_PI / 180;
constexpr static double RAD_TO_DEG = 180 / M_PI;

constexpr uint16_t B0 = 1 << 0;
constexpr uint16_t B1 = 1 << 1;
constexpr uint16_t B2 = 1 << 2;
constexpr uint16_t B3 = 1 << 3;
constexpr uint16_t B4 = 1 << 4;
constexpr uint16_t B5 = 1 << 5;
constexpr uint16_t B6 = 1 << 6;
constexpr uint16_t B7 = 1 << 7;
constexpr uint16_t B8 = 1 << 8;
constexpr uint16_t B9 = 1 << 9;
constexpr uint16_t B10 = 1 << 10;
constexpr uint16_t B11 = 1 << 11;
constexpr uint16_t B12 = 1 << 12;
constexpr uint16_t B13 = 1 << 13;
constexpr uint16_t B14 = 1 << 14;
constexpr uint16_t B15 = 1 << 15;

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
constexpr uint16_t DC1_VALUE1 = 0 | B14 | B13;
constexpr uint16_t DC1_VALUE2 = ~DC1_VALUE1;
constexpr uint16_t DC1_MASK = B15 | B14 | B13;
constexpr uint16_t DC2_VALUE1 = 0 | B14 | 0;
constexpr uint16_t DC2_VALUE2 = ~DC2_VALUE1;
constexpr uint16_t DC2_MASK = DC1_MASK;
constexpr uint16_t DC3_VALUE1 = B15 | B14 | B13;
constexpr uint16_t DC3_VALUE2 = ~DC3_VALUE1;
constexpr uint16_t DC3_MASK = DC1_MASK;
constexpr uint16_t DC4_VALUE1 = 0 | 0 | B13;
constexpr uint16_t DC4_VALUE2 = ~DC4_VALUE1;
constexpr uint16_t DC4_MASK = DC1_MASK;
constexpr uint16_t DC5_VALUE1 = 0 | B14 | B13;
constexpr uint16_t DC5_VALUE2 = 0 | 0 | 0;
constexpr uint16_t DC5_MASK = DC1_MASK;
constexpr uint16_t DC6_VALUE1 = 0 | 0 | B13;
constexpr uint16_t DC6_VALUE2 = 0 | B14 | 0;
constexpr uint16_t DC6_MASK = DC1_MASK;
constexpr uint16_t DC7_VALUE1 = B15 | B14 | B13;
constexpr uint16_t DC7_VALUE2 = B15 | 0 | 0;
constexpr uint16_t DC7_MASK = DC1_MASK;
constexpr uint16_t DC8_VALUE1 = B15 | 0 | B13;
constexpr uint16_t DC8_VALUE2 = B15 | B14 | 0;
constexpr uint16_t DC8_MASK = DC1_MASK;
constexpr uint16_t DC9_VALUE = 0;
constexpr uint16_t DC9_MASK = B12;
constexpr uint16_t DC10_VALUE = B11;
constexpr uint16_t DC10_MASK = B11;
constexpr uint16_t DC11_VALUE = B10;
constexpr uint16_t DC11_MASK = B10;
constexpr uint16_t DC12_VALUE = B9;
constexpr uint16_t DC12_MASK = B9;

class CduChannel {
public:
    double theta = 310.0 * DEG_TO_RAD; // Radians
    uint16_t read_counter = static_cast<uint16_t>(310.0 / TWENTY_ARCSECONDS);  // Multiplied by 20 arc-seconds to get degrees

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
