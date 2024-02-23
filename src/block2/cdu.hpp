#pragma once

#include <array>
#include <cmath>
#include <cstdint>
#include <thread>

namespace agcplusplus::block2 {
    // Angle-related constants.
    constexpr static double TWENTY_ARCSECONDS = 180 / std::pow(2, 15);
    constexpr static double DEG_TO_RAD = M_PI / 180;
    constexpr static double RAD_TO_DEG = 180 / M_PI;

    // Voltage-related constants.
    // The coarse and fine system transformers bring 26V RMS down to 4V RMS.
    constexpr double CDU_VOLTAGE = 4.0; // 8V RMS center-tapped, per ND-1021043 and drawing 1010725.
    constexpr double P2P_TO_RMS = 0.35355;
    // Coarse schmitt trigger is at 0.47 volts RMS, per Skylab PGNCS Mechanization Study Guide pg 3-25.
    // Other documentation is potentially erroneous.
    // Backed up by Mike Stewart's testing of flown CDUs.
    constexpr double COARSE_C1_TRIGGER = 0.47;
    constexpr double FINE_F2_TRIGGER = 4.0 * P2P_TO_RMS;    // 4 volts peak-to-peak
    constexpr double FINE_F1_TRIGGER = 0.200 * P2P_TO_RMS;  // 0.2 volts peak-to-peak

    // Bit positions for the read counter.
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

    // Coarse system definitions.
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
    // This is the logic for closing any of the coarse switches S1-S12.
    // There is a value and mask, the mask being applied first and then the value checked.
    // There may be more than one value per switch.
    constexpr uint16_t COARSE_S1_VALUE1 = 0 | B14 | B13;
    constexpr uint16_t COARSE_S1_VALUE2 = ~COARSE_S1_VALUE1;
    constexpr uint16_t COARSE_S1_MASK = B15 | B14 | B13;
    constexpr uint16_t COARSE_S2_VALUE1 = 0 | B14 | 0;
    constexpr uint16_t COARSE_S2_VALUE2 = ~COARSE_S2_VALUE1;
    constexpr uint16_t COARSE_S2_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S3_VALUE1 = B15 | B14 | B13;
    constexpr uint16_t COARSE_S3_VALUE2 = ~COARSE_S3_VALUE1;
    constexpr uint16_t COARSE_S3_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S4_VALUE1 = 0 | 0 | B13;
    constexpr uint16_t COARSE_S4_VALUE2 = ~COARSE_S4_VALUE1;
    constexpr uint16_t COARSE_S4_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S5_VALUE1 = 0 | B14 | B13;
    constexpr uint16_t COARSE_S5_VALUE2 = 0 | 0 | 0;
    constexpr uint16_t COARSE_S5_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S6_VALUE1 = 0 | 0 | B13;
    constexpr uint16_t COARSE_S6_VALUE2 = 0 | B14 | 0;
    constexpr uint16_t COARSE_S6_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S7_VALUE1 = B15 | B14 | B13;
    constexpr uint16_t COARSE_S7_VALUE2 = B15 | 0 | 0;
    constexpr uint16_t COARSE_S7_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S8_VALUE1 = B15 | 0 | B13;
    constexpr uint16_t COARSE_S8_VALUE2 = B15 | B14 | 0;
    constexpr uint16_t COARSE_S8_MASK = COARSE_S1_MASK;
    constexpr uint16_t COARSE_S9_VALUE = 0;
    constexpr uint16_t COARSE_S9_MASK = B12;
    constexpr uint16_t COARSE_S10_VALUE = B11;
    constexpr uint16_t COARSE_S10_MASK = B11;
    constexpr uint16_t COARSE_S11_VALUE = B10;
    constexpr uint16_t COARSE_S11_MASK = B10;
    constexpr uint16_t COARSE_S12_VALUE = B9;
    constexpr uint16_t COARSE_S12_MASK = B9;

    // Fine system definitions.
    // Yes the bit order is reversed now but the official documentation does it that way.
    constexpr uint16_t FINE_S1_VALUE1 = B8 | B9 | B10;
    constexpr uint16_t FINE_S1_VALUE2 = ~FINE_S1_VALUE1;
    constexpr uint16_t FINE_S1_MASK = B8 | B9 | B10;
    constexpr uint16_t FINE_S2_VALUE1 = 0 | B9 | B10;
    constexpr uint16_t FINE_S2_VALUE2 = ~FINE_S2_VALUE1;
    constexpr uint16_t FINE_S2_MASK = FINE_S1_MASK;
    constexpr uint16_t FINE_S3_VALUE1 = B8 | 0 | B10;
    constexpr uint16_t FINE_S3_VALUE2 = ~FINE_S3_VALUE1;
    constexpr uint16_t FINE_S3_MASK = FINE_S1_MASK;
    constexpr uint16_t FINE_S4_VALUE1 = 0 | 0 | B10;
    constexpr uint16_t FINE_S4_VALUE2 = ~FINE_S4_VALUE1;
    constexpr uint16_t FINE_S4_MASK = FINE_S1_MASK;
    constexpr uint16_t FINE_S5_VALUE1 = B10 | 0;
    constexpr uint16_t FINE_S5_VALUE2 = ~FINE_S5_VALUE1;
    constexpr uint16_t FINE_S5_MASK = B10 | B11;
    constexpr uint16_t FINE_S6_VALUE1 = B10 | B11;
    constexpr uint16_t FINE_S6_VALUE2 = ~FINE_S6_VALUE1;
    constexpr uint16_t FINE_S6_MASK = FINE_S5_MASK;
    constexpr uint16_t FINE_S7_VALUE = 0;
    constexpr uint16_t FINE_S7_MASK = B11;
    constexpr uint16_t FINE_S8_VALUE = B11;
    constexpr uint16_t FINE_S8_MASK = B11;
    constexpr uint16_t FINE_S9_VALUE = 0 | B10;
    constexpr uint16_t FINE_S9_MASK = B7 | B10;
    constexpr uint16_t FINE_S10_VALUE = B7 | B10;
    constexpr uint16_t FINE_S10_MASK = FINE_S9_MASK;
    constexpr uint16_t FINE_S11_VALUE = 0;
    constexpr uint16_t FINE_S11_MASK = B10;
    constexpr uint16_t FINE_S12_VALUE = 0 | 0;
    constexpr uint16_t FINE_S12_MASK = FINE_S9_MASK;
    constexpr uint16_t FINE_S13_VALUE = B7 | 0;
    constexpr uint16_t FINE_S13_MASK = FINE_S9_MASK;
    constexpr uint16_t FINE_S14_VALUE = B10;
    constexpr uint16_t FINE_S14_MASK = FINE_S11_MASK;
    constexpr uint16_t FINE_S15_MASK = B6;
    constexpr uint16_t FINE_S16_MASK = B5;
    constexpr uint16_t FINE_S17_MASK = B4;
    constexpr uint16_t FINE_S18_MASK = B3;
    constexpr uint16_t FINE_S19_MASK = B2;
    constexpr uint16_t FINE_S20_MASK = B1;
    constexpr uint16_t FINE_S21_MASK = B0;

    constexpr double FINE_BIAS = (62.0 / 10062.0);
    constexpr double FINE_11_25_BIT = (25000.0 / 125500.0);
    constexpr double FINE_240K = (25000.0 / 240000.0);
    constexpr double FINE_SIN_11_25 = (25000.0 / 128000.0);
    constexpr double FINE_SIN_33_75 = (25000.0 / 45000.0);
    constexpr double FINE_SIN_56_25 = (25000.0 / 30000.0);
    constexpr double FINE_SIN_78_75 = (25000.0 / 25500.0);
    constexpr double FINE_COS_11_25 = FINE_SIN_78_75;
    constexpr double FINE_COS_33_75 = FINE_SIN_56_25;
    constexpr double FINE_COS_56_25 = FINE_SIN_33_75;
    constexpr double FINE_COS_78_75 = FINE_SIN_11_25;

    enum COUNT_DIRECTION {
        NONE,
        UP,
        DOWN,
    };

    enum COUNT_SPEED {
        LOW,            // 800 cps
        HIGH            // 12800 cps
    };

    enum MODE {
        NORMAL,
        COARSE_ALIGN
    };

    class CduChannel {
    public:
        double theta = 70.0 * DEG_TO_RAD; // Radians
        uint16_t read_counter = static_cast<uint16_t>(0 / TWENTY_ARCSECONDS);  // Multiplied by 20 arc-seconds to get degrees
        uint16_t prev_read_counter = 0;
        double prev_coarse_error = 0.0;
        double prev_fine_error = 0.0;
        bool zero_discrete = false;
        bool should_count = false;
        COUNT_DIRECTION count_direction = NONE;
        COUNT_SPEED count_speed = HIGH;
        MODE mode = NORMAL;

        [[nodiscard]] double coarse_error() const;
        [[nodiscard]] double fine_error(double msa_gain) const;
    };

    class Cdu {
    public:
        uint64_t cur_state = UINT64_MAX;
        uint64_t prev_state = 0;
        bool iss_phase1_state = false;
        bool prev_iss_phase1_state = iss_phase1_state;

        void tick_cmc();
        [[noreturn]] void tick_iss();
        void refresh_channels();
        void set_iss_cdu_zero(bool state);
        void set_oss_cdu_zero(bool state);

    private:
        std::array<CduChannel, 3> channels{};
        std::thread iss_timing_thread;
    };
}
