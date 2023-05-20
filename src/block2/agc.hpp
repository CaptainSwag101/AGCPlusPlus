#include "cpu.hpp"
#include "block2defs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include <iostream>
#include <map>
#include <vector>

#pragma once

namespace agcplusplus::block2 {
class Agc {
public:
    Agc(std::vector<word>& rope, std::map<word, word> padload, InitArguments init_args);
    void run();

private:
    std::shared_ptr<Cpu> cpu;
    std::shared_ptr<Memory> memory;
    std::shared_ptr<Scaler> scaler;
    std::shared_ptr<Timer> timer;
};
}
