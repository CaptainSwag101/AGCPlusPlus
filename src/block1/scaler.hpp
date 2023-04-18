#include "block1defs.hpp"

#pragma once

namespace agcplusplus::block1 {
    class Scaler {
    public:
        void tick();

    private:
        uint64_t current_tick = 0;
        uint64_t previous_tick = 0;
    };
}
