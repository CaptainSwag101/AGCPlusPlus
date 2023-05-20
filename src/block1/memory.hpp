#include "block1defs.hpp"
#include "../common/global_definitions.hpp"

#include <array>
#include <vector>

#pragma once

namespace agcplusplus::block1 {
    class Memory {
    public:
        word read(word address, word bank);
        void write(word address, word data);
        void assign_fixed_memory(std::vector<word> buffer);
    private:
        std::array<word, MEM_ERASABLE_SIZE> erasable{};
        std::array<word, MEM_FIXED_TOTAL_SIZE> fixed{};
    };
}
