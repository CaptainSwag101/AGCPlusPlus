#include "cpu.hpp"
#include "memory.hpp"
#include <iostream>

#pragma once

class Agc {
public:
    Agc();

    Cpu cpu;
    Memory memory;
};