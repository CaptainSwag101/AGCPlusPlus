#include "block1defs.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"

#include <memory>
#include <thread>

#pragma once

namespace agcplusplus::block1 {
    class Agc {
    public:
        static Timer timer;
        static Scaler scaler;
        static Memory memory;
        static Cpu cpu;
        static std::thread dsky_thread;

        [[noreturn]] void run();
    };
}
