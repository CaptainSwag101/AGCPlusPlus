#include "cpu.hpp"
#include "memory.hpp"
#include <iostream>

#pragma once

namespace agcplusplus {
    class Agc {
    public:
        Agc();
        void run();

        Cpu cpu;
        Memory memory;
    };
}
