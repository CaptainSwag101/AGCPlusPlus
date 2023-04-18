#include "block1defs.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"

#include <memory>

#pragma once

namespace agcplusplus::block1 {
    class Agc {
    public:
        static Timer timer;
        static Scaler scaler;
        static Memory memory;
        static Cpu cpu;

        [[noreturn]] void run();
    };
}
