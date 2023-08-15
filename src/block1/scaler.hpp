#include <queue>
#include "block1defs.hpp"

#pragma once

namespace agcplusplus::block1 {
    class Scaler {
    public:
        void tick();
        std::queue<std::tuple<word, word>> dsky_queue;
        void interrupt_started();
        void interrupt_ended();
        void tc_started();
        void tc_ended();

    private:
        uint64_t current_tick = 0;
        uint64_t previous_tick = 0;
        bool nrptal_disarm = true;  // Prevents "no rupt" alarm by indicating valid rupt behavior
        bool rptal_disarm = true;   // Prevents "rupt lock" alarm by indicating valid rupt behavior
        bool ntcal_disarm = true;   // Prevents "no TC" alarm by indicating valid code execution
        bool tcal_disarm = true;    // Prevents "TC trap" alarm by indicating valid code execution
    };
}
