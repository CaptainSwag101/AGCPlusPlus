#include "../common/global_definitions.hpp"

#pragma once

namespace agcplusplus::block1 {
    constexpr uint64_t MEM_ERASABLE_START = 0;
    constexpr uint64_t MEM_ERASABLE_END = 01777;
    constexpr uint64_t MEM_ERASABLE_SIZE = MEM_ERASABLE_END - MEM_ERASABLE_START + 1;

    constexpr uint64_t MEM_FIXED_FIXED_START = 02000;
    constexpr uint64_t MEM_FIXED_FIXED_END = 05777;
    constexpr uint64_t MEM_FIXED_FIXED_SIZE = MEM_FIXED_FIXED_END - MEM_FIXED_FIXED_START + 1;

    constexpr uint64_t MEM_FIXED_BANKED_START = 06000;
    constexpr uint64_t MEM_FIXED_BANKED_END = 07777;
    constexpr uint64_t MEM_FIXED_BANKED_SIZE = MEM_FIXED_BANKED_END - MEM_FIXED_BANKED_START + 1;
    constexpr uint64_t MEM_FIXED_BANKED_BANKCOUNT = 034;    // However, banks 015, 016, 017, and 020 are not wired in real hardware.

    constexpr uint64_t MEM_FIXED_TOTAL_SIZE = MEM_FIXED_FIXED_SIZE + (MEM_FIXED_BANKED_SIZE * MEM_FIXED_BANKED_BANKCOUNT);

    enum class COUNTER_STATUS {
        NONE = 0,
        UP = 1,
        DOWN = 2
    };

    constexpr word COUNTER_OVCTR = 0;
    constexpr word COUNTER_TIME2 = 1;
    constexpr word COUNTER_TIME1 = 2;
    constexpr word COUNTER_TIME3 = 3;
    constexpr word COUNTER_TIME4 = 4;
    constexpr word COUNTER_UPLINK = 5;
    constexpr word COUNTER_OUTCR1 = 6;
    constexpr word COUNTER_OUTCR2 = 7;
    constexpr word COUNTER_PIPAX = 8;
    constexpr word COUNTER_PIPAY = 9;
    constexpr word COUNTER_PIPAZ = 10;
    constexpr word COUNTER_CDUX = 11;
    constexpr word COUNTER_CDUY = 12;
    constexpr word COUNTER_CDUZ = 13;
    constexpr word COUNTER_OPTX = 14;
    constexpr word COUNTER_OPTY = 15;
    constexpr word COUNTER_TRKRX = 16;
    constexpr word COUNTER_TRKRY = 17;
    constexpr word COUNTER_TRKRR = 18;
    constexpr word COUNTER_OUTCR3 = 19;

    constexpr word RUPT_RP1 = 0;    // T3RUPT
    constexpr word RUPT_TRP2 = 1;   // Unused
    constexpr word RUPT_RP3 = 2;    // Unknown
    constexpr word RUPT_TRP4 = 3;   // KEYRUPT
    constexpr word RUPT_RP5 = 4;    // UPRUPT
    constexpr word RUPT_DKEND = 5;  // DOWNRUPT
}

