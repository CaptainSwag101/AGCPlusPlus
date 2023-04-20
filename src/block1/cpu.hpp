#include "block1defs.hpp"

#pragma once

namespace agcplusplus::block1 {
    class Cpu {
    public:
        // Functions
        void tick();
        void process_before_timepulse();
        void process_timepulse();
        void process_after_timepulse();

        // Central registers
        word a, q, z, lp, x, y, b, g;
        word write_bus;

        // I/O registers
        word in[4];
        word out[5];

        // Auto-generated (read-only) registers
        word u, c, p, p2;

        // Control-related registers
        word sq, st, s, bank, timepulse = 1;
    };
}
