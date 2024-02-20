#include <functional>
#include <memory>
#include <unordered_map>
#include "block2defs.hpp"
#include "memory.hpp"

#pragma once

namespace agcplusplus::block2 {

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

class Cpu {
public:
    // Init functions
    void start();

    // Activity functions
    void tick();
    void process_before_timepulse();
    void process_timepulse();
    void process_after_timepulse();
    void queue_gojam();
    void update_adder();
    void update_bb();
    void update_eb_fb();

    // Memory functions
    word get_erasable_absolute_addr();
    word get_fixed_absolute_addr() const;

    // Debug functions
    void print_state_info(std::ostream& output) const;

    // Registers
    word a{}, l{}, g{}, b{}, z{}, q{}, s{}, s_temp{};
    word sq{}, fext{}, eb{}, fb{}, bb{}, u{}, x{}, y{};
    uint8_t st{}, st_next{}, br{};
    bool explicit_carry{};

    // Interrupt/Counter cells
    std::array<bool, 11> interrupts{};  // Interrupt request cells
    std::array<word, 20> counters{};    // Can be 0, +1, -1, or both in the case of a freak accident

    // I/O
    word read_io_channel(word address);
    void write_io_channel(word address, word data);
    std::unordered_map<word, word> io_channels;

    // Internal CPU data
    word write_bus{}, dv_stage{};
    bool fetch_next_instruction{}, inhibit_interrupts{}, no_eac{}, mcro{}, dv{};
    bool inkl{}, iip{}, pseudo{}, shinc{}, pifl{}, extend{}, extend_next{}, restart{};
    bool night_watchman{};

    // Instruction data
    uint8_t timepulse = 1;
    subinstruction current_subinstruction{};

private:
    void gojam();
    bool should_gojam{};
};
}
