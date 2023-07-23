#include <queue>
#include "block1defs.hpp"

#pragma once

namespace agcplusplus::block1 {
    class Scaler {
    public:
        void tick();
        std::queue<std::tuple<word, word>> dsky_queue;

    private:
        uint64_t current_tick = 0;
        uint64_t previous_tick = 0;

        //DEBUG: Timing related debug info
        uint64_t debug_start_tick = 0;
        uint64_t debug_end_tick = 0;
    };
}
