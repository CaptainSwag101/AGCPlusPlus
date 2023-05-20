#pragma once

#include "block1defs.hpp"

namespace agcplusplus::block1 {
    class Timer {
    public:
        void start();
        void execute_tick_batch();
        void tick();

    private:
        uint64_t total_ticks = 0;
        // Timing variables for batching execution for timing accuracy
        constexpr static uint64_t TIMEPULSES_PER_SECOND = 1024000;
        constexpr static uint64_t TIMEPULSES_PER_MILLISECOND = TIMEPULSES_PER_SECOND / 1000;
    };
}
