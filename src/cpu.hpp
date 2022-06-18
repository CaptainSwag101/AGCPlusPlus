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
    uint8_t sequence_opcode;
    std::string name;
    std::function<void(Cpu&)> function;
};

enum class LoggingVerbosity {
    None,
    CpuStatePerMCT,
    CpuStatePerTimepulse,
};

class Cpu {
public:
    // Init functions
    Cpu(InitArguments init_args);
    void assign_memory(std::shared_ptr<Memory> mem);

    // Activity functions
    void tick();
    void gojam();
    void update_adder();
    void update_bb();
    void update_eb_fb();

    // Memory functions
    word get_erasable_absolute_addr() const;
    word get_fixed_absolute_addr() const;

    // Debug functions
    void print_state_info(std::ostream& output) const;

    // Helper data
    LoggingVerbosity verbosity;

    // Pointers
    std::shared_ptr<Memory> memory;

    // Registers
    word a, l, g, b, z, q, s, s_temp, sq, eb, fb, bb, u, x, y;
    uint8_t st, st_next, br;
    bool explicit_carry;

    // Interrupt/Counter cells
    bool ignore_interrupts; // Debug override
    bool interrupts[11];    // Interrupt request cells
    bool ignore_counters;   // Debug override
    word counters[20];  // Can be 0, +1, -1, or both in the case of a freak accident

    // I/O
    word read_io_channel(word address);
    void write_io_channel(word address, word data);
    std::unordered_map<word, word> io_channels;

    // Internal CPU data
    word write_bus;
    bool fetch_next_instruction, inhibit_interrupts, no_eac, mcro, dv;
    bool inkl, iip, sudo, shinc, pifl, extend, extend_next, restart;
    uint64_t night_watchman;
    word interrupt_being_serviced;

    // Instruction data
    uint8_t current_timepulse = 1;
    subinstruction current_subinstruction;
    subinstruction pending_subinstruction;
};
}
