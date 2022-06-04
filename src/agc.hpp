#include "cpu.hpp"
#include "globaldefs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include <array>
#include <iostream>

#pragma once

namespace agcplusplus {
class Agc {
public:
    Agc(std::array<word, SIZE_FIXED_MEM> rope, bool logMCT, bool logTimepulse);
    void run();

private:
    Cpu cpu;
    Memory memory;
    Scaler scaler;
    Timer timer;
};
}
