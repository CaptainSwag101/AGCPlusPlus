#include "block1defs.hpp"
#include "../common/global_definitions.hpp"

#include <array>

#pragma once

namespace agcplusplus::block1 {
    class Memory {
    public:
        std::array<word, MEM_ERASABLE_SIZE> erasable;
        std::array<word, MEM_FIXED_TOTAL_SIZE> fixed;
    };
}