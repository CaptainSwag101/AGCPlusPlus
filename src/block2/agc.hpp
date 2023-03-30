#include "cpu.hpp"
#include "block2defs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include <array>
#include <iostream>

#pragma once

namespace agcplusplus::block2 {
class Agc {
public:
    Agc(std::vector<word>& rope, InitArguments init_args);
    void run();

private:
    std::shared_ptr<Cpu> cpu;
    std::shared_ptr<Memory> memory;
    std::shared_ptr<Scaler> scaler;
    std::shared_ptr<Timer> timer;
};
}
