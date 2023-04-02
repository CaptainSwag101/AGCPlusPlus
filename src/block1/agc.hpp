#include "block1defs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"

#include <memory>

#pragma once

namespace agcplusplus::block1 {
    class Agc {
    public:
        static Timer timer;
        static Scaler scaler;
        static Memory memory;

        [[noreturn]] void run();

    private:
        ComponentState state = ComponentState::Off;
    };
}
