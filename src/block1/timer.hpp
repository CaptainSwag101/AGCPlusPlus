#pragma once

#include "block1defs.hpp"

namespace agcplusplus::block1 {
    class Timer {
    public:
        void execute_tick_batch();
        void tick();

        uint64_t total_ticks = 0;

        // Timing variables for batching execution for timing accuracy
        constexpr static uint64_t TIMEPULSES_PER_SECOND = 1024000;
        constexpr static uint64_t TIMEPULSES_PER_MILLISECOND = TIMEPULSES_PER_SECOND / 1000;

        //DEBUG: Timing related debug info
        uint64_t debug_start_tick = 0;
        uint64_t debug_end_tick = 0;
    };
}
