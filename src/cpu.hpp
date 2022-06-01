#include <functional>
#include <memory>
#include <unordered_map>
#include "globaldefs.hpp"
#include "memory.hpp"

#pragma once

namespace agcplusplus {

// Forward declaration of Cpu class for subinstruction struct
class Cpu;

struct subinstruction {
    uint8_t stage;
    bool sequence_extend;
    uint8_t sequence_mask;
    uint8_t sequence_minval;
    std::string name;
    std::function<void(Cpu&)> function;
};

class Cpu {
public:
    // Init functions
    Cpu();
    void assign_mem(Memory& mem);

    // Activity functions
    void tick();
    void update_adder();
    void update_bb();

    // Debug functions
    void print_state_info(std::ostream& output) const;

    // Pointers
    std::unique_ptr<Memory> memory;

    // Registers
    word a, l, g, b, z, q, s, s_temp, sq, eb, fb, bb, u, x, y;
    uint8_t st, st_next, br;
    bool explicit_carry;

    // I/O
    std::unordered_map<word, word> io_channels;

    // Internal CPU data
    word write_bus;
    bool fetch_next_instruction, inhibit_interrupts, no_eac, mcro, dv, shinc, pifl, extend, extend_next;
    uint64_t night_watchman;

    // Instruction data
    uint8_t current_timepulse;
    subinstruction current_subinstruction;
};
}
