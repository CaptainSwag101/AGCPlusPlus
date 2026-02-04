#pragma once

#include "../common/global_definitions.hpp"
#include <map>

namespace agcplusplus::block2 {
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

enum COUNTER_TYPE {
    PINC,
    PINC_MINC,
    DINC,
    PCDU_MCDU,
    SHINC,
    SHINC_SHANC
};
const std::map<word, COUNTER_TYPE> COUNTER_INSTRUCTION_TYPES = {
    {COUNTER_TIME2, PINC},
    {COUNTER_TIME1, PINC},
    {COUNTER_TIME3, PINC},
    {COUNTER_TIME4, PINC},
    {COUNTER_TIME5, PINC},
    {COUNTER_TIME6, DINC},
    {COUNTER_CDUX, PCDU_MCDU},
    {COUNTER_CDUY, PCDU_MCDU},
    {COUNTER_CDUZ, PCDU_MCDU},
    {COUNTER_TRN, PCDU_MCDU},
    {COUNTER_SHFT, PCDU_MCDU},
    {COUNTER_PIPAX, PINC_MINC},
    {COUNTER_PIPAY, PINC_MINC},
    {COUNTER_PIPAZ, PINC_MINC},
    {COUNTER_BMAGX, PINC_MINC},
    {COUNTER_BMAGY, PINC_MINC},
    {COUNTER_BMAGZ, PINC_MINC},
    {COUNTER_INLINK, SHINC_SHANC},
    {COUNTER_RNRAD, SHINC_SHANC},
    {COUNTER_GYROD, DINC},
    {COUNTER_CDUXD, DINC},
    {COUNTER_CDUYD, DINC},
    {COUNTER_CDUZD, DINC},
    {COUNTER_TRUND, DINC},
    {COUNTER_SHAFTD, DINC},
    {COUNTER_THRSTD, DINC},
    {COUNTER_EMSD, DINC},
    {COUNTER_OTLNK, SHINC},
    {COUNTER_ALT, SHINC},
};

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
}
