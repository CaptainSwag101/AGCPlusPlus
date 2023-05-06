#include "block1defs.hpp"

#include <functional>
#include <iostream>
#include <iomanip>

#pragma once

namespace agcplusplus::block1 {
// Forward-declare the CPU class for the subinstruction struct
    class Cpu;

    struct subinstruction {
        std::string name;
        uint8_t stage;
        bool extended;
        uint8_t mask;
        uint8_t order_code;
        std::function<void(Cpu&)> function;
    };

    class Cpu {
    public:
        // Functions
        void go();
        void tick();
        void process_before_timepulse();
        void process_timepulse();
        void process_after_timepulse();
        void update_adder();
        void print_state_info(std::ostream& output) const;

        // Central registers
        word a{}, q{}, z{}, lp{}, x{}, y{}, b{}, g{};
        word write_bus{};
        bool carry_in = false;

        // I/O registers
        word in[4]{};
        word out[5]{};

        // Auto-generated (read-only) registers
        word u{}, c{}, p{}, p2{};

        // Control-related registers
        word sq{}, st{}, st_next{}, s{}, s_temp{}, br{}, bank{}, timepulse = 1;
        subinstruction current_subinstruction, pending_subinstruction;
        bool fetch_new_subinstruction = false;
        bool extend = false, extend_next = false, no_eac = false, inkl = false, inhibit_interrupts = false;
    };
}
