#include <cstdint>
#include <iomanip>
#include <iostream>

#pragma once

namespace agcplusplus {
    // Simplify our terminology by using "words" just like the AGC
    using word = uint16_t;

    constexpr word BITMASK_1_2 = ((1 << 2) - 1);
    constexpr word BITMASK_1_10 = ((1 << 10) - 1);
    constexpr word BITMASK_1_12 = ((1 << 12) - 1);
    constexpr word BITMASK_1_14 = ((1 << 14) - 1);
    constexpr word BITMASK_1_15 = ((1 << 15) - 1);
    constexpr word BITMASK_1_16 = ((1 << 16) - 1);
    constexpr word BITMASK_4_15 = 0077770;
    constexpr word BITMASK_8_10 = 0003400;
    constexpr word BITMASK_8_14 = 0037600;
    constexpr word BITMASK_10_14 = 0037000;
    constexpr word BITMASK_11_15 = 0076000;
    constexpr word BITMASK_11_16 = 0176000;
    constexpr word BITMASK_13_14 = 0030000;
    constexpr word BITMASK_14_15 = 0060000;
    constexpr word BITMASK_15_16 = 0140000;
    constexpr word BITMASK_2 = (1 << 1);
    constexpr word BITMASK_3 = (1 << 2);
    constexpr word BITMASK_4 = (1 << 3);
    constexpr word BITMASK_5 = (1 << 4);
    constexpr word BITMASK_6 = (1 << 5);
    constexpr word BITMASK_7 = (1 << 6);
    constexpr word BITMASK_8 = (1 << 7);
    constexpr word BITMASK_9 = (1 << 8);
    constexpr word BITMASK_10 = (1 << 9);
    constexpr word BITMASK_11 = (1 << 10);
    constexpr word BITMASK_12 = (1 << 11);
    constexpr word BITMASK_13 = (1 << 12);
    constexpr word BITMASK_14 = (1 << 13);
    constexpr word BITMASK_15 = (1 << 14);
    constexpr word BITMASK_16 = (1 << 15);
    constexpr word BITMASK_11_14 = (BITMASK_11 | BITMASK_12 | BITMASK_13 | BITMASK_14);
    constexpr word BITMASK_13_16 = (BITMASK_13 | BITMASK_14 | BITMASK_15 | BITMASK_16);
    constexpr uint64_t BITMASK_17 = (1 << 16);

    struct InitArguments {
        bool log_mct;
        bool log_timepulse;
        bool log_memory;
        bool ignore_counters;
        bool ignore_interrupts;
        bool ignore_alarms;
    };
}
