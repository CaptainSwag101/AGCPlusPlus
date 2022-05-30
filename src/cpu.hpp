#include <iostream>
#include <unordered_map>
#include "globaldefs.hpp"

#pragma once

class Cpu {
public:
    Cpu();
    void tick();

private:
    // Registers
    word a, l, g, b, z, q, s, s_temp, sq, eb, fb, bb, u, x, y;
    uint8_t st, st_next, br;

    // I/O
    std::unordered_map<word, word> io_channels;

    // Internal CPU data
    bool fetch_next_instruction, inhibit_interrupts, no_eac, mcro, dv, shinc, pifl, extend, extend_next;
    uint64_t night_watchman;
};
