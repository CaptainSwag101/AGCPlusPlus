#include <functional>
#include <map>
#include <memory>
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

class io_channel {
public:
    void write(word data) {
        _prev_state = _current_state;
        _current_state = data;
        _diff = _current_state ^ _prev_state;
    }
    [[nodiscard]] word read() const {
        return _current_state;
    }
    [[nodiscard]] word diff() const {
        return _diff;
    }
    [[nodiscard]] bool were_bits_changed(const word mask) const {
        return (_diff & mask) == mask;
    }
    // Bit number is 1-based
    [[nodiscard]] bool are_bits_set(const word mask) const {
        return (_current_state & mask) == mask;
    }
private:
    word _current_state = ~0;
    word _prev_state = 0;
    word _diff = ~0;
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
    [[nodiscard]] static word get_erasable_absolute_addr(word address, word bank);
    [[nodiscard]] static word get_fixed_absolute_addr(word address, word bank, word superbank);

    // Debug functions
    void print_state_info(std::ostream& output) const;

    // Registers
    word a{}, l{}, g{}, b{}, z{}, q{}, s{}, s_writeback{};
    word sq{}, fext{}, eb{}, fb{}, bb{}, u{}, x{}, y{};
    uint8_t st{}, st_next{}, br{};
    bool explicit_carry{};

    // Interrupt/Counter cells
    std::array<bool, 11> interrupts{};  // Interrupt request cells
    std::array<word, 28> counters{};    // Can be 0, +1, -1, or both in the case of a freak accident

    // I/O
    word read_io_channel(word address);
    void write_io_channel(word address, word data);
    std::map<int, io_channel> io_channels{};

    // Internal CPU data
    word write_bus{}, dv_stage{};
    bool fetch_next_instruction{}, inhibit_interrupts{}, no_eac{}, mcro{}, dv{};
    bool inkl{}, iip{}, pseudo{}, shinc{}, pifl{}, extend{}, extend_next{}, restart{};
    bool night_watchman{};
    bool channel_access{};

    // Instruction data
    uint8_t timepulse = 1;
    subinstruction current_subinstruction{};

private:
    void gojam();
    bool should_gojam{};
};
}
