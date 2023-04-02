#include "../common/global_definitions.hpp"

#pragma once

namespace agcplusplus::block1 {
    enum class ComponentState {
        Off,
        Stopped,
        Started,
    };

    constexpr uint64_t MEM_ERASABLE_START = 0;
    constexpr uint64_t MEM_ERASABLE_END = 01777;
    constexpr uint64_t MEM_ERASABLE_SIZE = MEM_ERASABLE_END - MEM_ERASABLE_START;

    constexpr uint64_t MEM_FIXED_FIXED_START = 02000;
    constexpr uint64_t MEM_FIXED_FIXED_END = 05777;
    constexpr uint64_t MEM_FIXED_FIXED_SIZE = MEM_FIXED_FIXED_END - MEM_FIXED_FIXED_START;

    constexpr uint64_t MEM_FIXED_BANKED_START = 06000;
    constexpr uint64_t MEM_FIXED_BANKED_END = 07777;
    constexpr uint64_t MEM_FIXED_BANKED_SIZE = MEM_FIXED_BANKED_END - MEM_FIXED_BANKED_START;
    constexpr uint64_t MEM_FIXED_BANKED_BANKCOUNT = 034;    // However, banks 015, 016, 017, and 020 are not wired in real hardware.

    constexpr uint64_t MEM_FIXED_TOTAL_SIZE = MEM_FIXED_FIXED_SIZE + (MEM_FIXED_BANKED_SIZE * MEM_FIXED_BANKED_BANKCOUNT);
}

