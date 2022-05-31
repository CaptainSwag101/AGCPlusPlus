#include <memory>
#include <unordered_map>
#include "globaldefs.hpp"
#include "memory.hpp"

#pragma once

namespace agcplusplus {
class Cpu {
public:
    Cpu();
    void assign_mem(Memory& mem);
    void tick();
    void update_adder();
    void update_bb();
    void print_state_info(std::ostream& output) const;

    // Pointers
    std::unique_ptr<Memory> memory;
    std::unique_ptr<std::minstd_rand> random_generator;

    // Registers
    word a, l, g, b, z, q, s, s_temp, sq, eb, fb, bb, u, x, y;
    uint8_t st, st_next, br;
    bool explicit_carry;

    // I/O
    std::unordered_map<word, word> io_channels;

    // Internal CPU data
    bool fetch_next_instruction, inhibit_interrupts, no_eac, mcro, dv, shinc, pifl, extend, extend_next;
    uint64_t night_watchman;

    // Instruction data

};
}
