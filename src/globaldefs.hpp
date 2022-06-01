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
constexpr word BITMASK_16 = (1 << 15);
}
