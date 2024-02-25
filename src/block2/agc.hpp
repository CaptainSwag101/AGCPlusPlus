#pragma once

#include "cpu.hpp"
#include "cdu.hpp"
#include "block2defs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include <fstream>
#include <map>
#include <vector>

namespace agcplusplus::block2 {
class Agc {
public:
    static Cpu cpu;
    static Memory memory;
    static Scaler scaler;
    static Timer timer;
    static Cdu cdu;
    static InitArguments config;
    static std::ofstream log_stream;

    Agc(const std::vector<word>& rope, const std::map<word, word>& padload, InitArguments init_args);
    void run();
};
}
