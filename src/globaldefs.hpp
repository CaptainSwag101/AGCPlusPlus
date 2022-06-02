#include <cstdint>
#include <iomanip>
#include <iostream>

#pragma once

namespace agcplusplus {
// Simplify our terminology by using "words" just like the AGC
using word = uint16_t;

constexpr word BITMASK_1_12 = ((1 << 12) - 1);
constexpr word BITMASK_1_14 = ((1 << 14) - 1);
constexpr word BITMASK_1_16 = ((1 << 16) - 1);
constexpr word BITMASK_7_14 = 037600;
constexpr word BITMASK_10_14 = 037000;
constexpr word BITMASK_11_15 = 076000;
constexpr word BITMASK_16 = (1 << 15);

constexpr word MEM_ERASABLE_START = 0;
constexpr word MEM_ERASABLE_END = 01777;
constexpr word MEM_ERASABLE_BANKED_START = 01400;
constexpr word MEM_ERASABLE_BANKED_END = 01777;
constexpr word MEM_FIXED_START = 02000;
constexpr word MEM_FIXED_END = 07777;
constexpr word MEM_FIXED_BANKED_START = 02000;
constexpr word MEM_FIXED_BANKED_END = 03777;

constexpr double FREQUENCY_CPU = 1024000.0;
}
