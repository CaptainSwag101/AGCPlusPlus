#include <cstdint>
#include <iomanip>
#include <iostream>

#pragma once

namespace agcplusplus {
// Simplify our terminology by using "words" just like the AGC
using word = uint16_t;

constexpr word BITMASK_1_2  = ((1 << 2) - 1);
constexpr word BITMASK_1_10 = ((1 << 10) - 1);
constexpr word BITMASK_1_12 = ((1 << 12) - 1);
constexpr word BITMASK_1_14 = ((1 << 14) - 1);
constexpr word BITMASK_1_16 = ((1 << 16) - 1);
constexpr word BITMASK_4_15  = 0077770;
constexpr word BITMASK_8_10  = 0001600;
constexpr word BITMASK_8_14  = 0037400;
constexpr word BITMASK_10_14 = 0037000;
constexpr word BITMASK_11_15 = 0076000;
constexpr word BITMASK_15_16 = 0140000;
constexpr word BITMASK_5 = (1 << 4);
constexpr word BITMASK_6 = (1 << 5);
constexpr word BITMASK_7 = (1 << 6);
constexpr word BITMASK_8 = (1 << 7);
constexpr word BITMASK_9 = (1 << 8);
constexpr word BITMASK_10 = (1 << 9);
constexpr word BITMASK_15 = (1 << 14);
constexpr word BITMASK_16 = (1 << 15);
constexpr uint64_t BITMASK_17 = (1 << 16);

constexpr uint64_t SIZE_ERASABLE_MEM = 2048;
constexpr uint64_t SIZE_FIXED_MEM = 36864;

constexpr word MEM_ERASABLE_START = 0;
constexpr word MEM_ERASABLE_END = 01777;
constexpr word MEM_ERASABLE_BANKED_START = 01400;
constexpr word MEM_ERASABLE_BANKED_END = 01777;
constexpr word MEM_FIXED_START = 02000;
constexpr word MEM_FIXED_END = 07777;
constexpr word MEM_FIXED_BANKED_START = 02000;
constexpr word MEM_FIXED_BANKED_END = 03777;

constexpr word COUNTER_TIME2 = 0;
constexpr word COUNTER_TIME1 = 1;
constexpr word COUNTER_TIME3 = 2;
constexpr word COUNTER_TIME4 = 3;
constexpr word COUNTER_TIME5 = 4;
constexpr word COUNTER_TIME6 = 5;
constexpr word COUNTER_CDUX = 6;
constexpr word COUNTER_CDUY = 7;
constexpr word COUNTER_CDUZ = 8;
constexpr word COUNTER_TRN = 9;
constexpr word COUNTER_SHFT = 10;
constexpr word COUNTER_PIPAX = 11;
constexpr word COUNTER_PIPAY = 12;
constexpr word COUNTER_PIPAZ = 13;
constexpr word COUNTER_BMAGX = 14;
constexpr word COUNTER_BMAGY = 15;
constexpr word COUNTER_BMAGZ = 16;
constexpr word COUNTER_INLINK = 17;
constexpr word COUNTER_RNRAD = 18;
constexpr word COUNTER_GYROD = 19;
constexpr word COUNTER_CDUXD = 20;
constexpr word COUNTER_CDUYD = 21;
constexpr word COUNTER_CDUZD = 22;
constexpr word COUNTER_TRUND = 23;
constexpr word COUNTER_SHAFTD = 24;
constexpr word COUNTER_THRSTD = 25;
constexpr word COUNTER_EMSD = 26;
constexpr word COUNTER_OTLNK = 27;
constexpr word COUNTER_ALT = 28;

constexpr word COUNT_DIRECTION_NONE = 0;
constexpr word COUNT_DIRECTION_UP = 1;
constexpr word COUNT_DIRECTION_DOWN = 2;

constexpr word RUPT_GO = 0;
constexpr word RUPT_T6RUPT = 1;
constexpr word RUPT_T5RUPT = 2;
constexpr word RUPT_T3RUPT = 3;
constexpr word RUPT_T4RUPT = 4;
constexpr word RUPT_KEYRUPT1 = 5;
constexpr word RUPT_KEYRUPT2 = 6;
constexpr word RUPT_MARKRUPT = 6;   // Same code as RUPT_KEYRUPT2
constexpr word RUPT_UPRUPT = 7;
constexpr word RUPT_DOWNRUPT = 8;
constexpr word RUPT_RADARRUPT = 9;
constexpr word RUPT_RUPT10L = 10;

struct InitArguments {
    bool log_mct;
    bool log_timepulse;
    bool ignore_counters;
    bool ignore_interrupts;
};
}
