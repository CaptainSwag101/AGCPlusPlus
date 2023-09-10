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
    static Cpu cpu;
    static Memory memory;
    static Scaler scaler;
    static Timer timer;
    static InitArguments config;

    Agc(const std::vector<word>& rope, const std::map<word, word>& padload, InitArguments init_args);
    void run();
};
}
