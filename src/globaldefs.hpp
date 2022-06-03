#include <cstdint>
#include <iomanip>
#include <iostream>

#pragma once

namespace agcplusplus {
// Simplify our terminology by using "words" just like the AGC
using word = uint16_t;

constexpr word BITMASK_1_10 = ((1 << 10) - 1);
constexpr word BITMASK_1_12 = ((1 << 12) - 1);
constexpr word BITMASK_1_14 = ((1 << 14) - 1);
constexpr word BITMASK_1_16 = ((1 << 16) - 1);
constexpr word BITMASK_8_14  = 0037400;
constexpr word BITMASK_10_14 = 0037000;
constexpr word BITMASK_11_15 = 0076000;
constexpr word BITMASK_15_16 = 0140000;
constexpr word BITMASK_15 = (1 << 14);
constexpr word BITMASK_16 = (1 << 15);

constexpr uint64_t SIZE_ERASABLE_MEM = 2048;
constexpr uint64_t SIZE_FIXED_MEM = 36864;

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
