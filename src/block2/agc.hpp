#include "cpu.hpp"
#include "block2defs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include "../common/logger.h"
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
    static Logger logger;

    Agc(const std::vector<word>& rope, const std::map<word, word>& padload, const InitArguments& init_args);
    void run();
};
}
