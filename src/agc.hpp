#include "cpu.hpp"
#include "globaldefs.hpp"
#include "memory.hpp"
#include <array>
#include <iostream>

#pragma once

namespace agcplusplus {
class Agc {
public:
    Agc(std::array<word, SIZE_FIXED_MEM> rope);
    void run();

    Cpu cpu;
    Memory memory;
};
}
