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
    std::shared_ptr<Cpu> cpu;
    std::shared_ptr<Memory> memory;
    std::shared_ptr<Scaler> scaler;
    std::shared_ptr<Timer> timer;
};
}
