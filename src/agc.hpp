#include "cpu.hpp"
#include "memory.hpp"
#include <iostream>

#pragma once

class Agc {
public:
    Agc();
    void Run();

    Cpu cpu;
    Memory memory;
};
