#include "globaldefs.hpp"
#include "cpu.hpp"

#include "control_pulses.cpp"

#pragma once

namespace agcplusplus {
void ad0(Cpu& cpu);
void ca0(Cpu& cpu);
void ccs0(Cpu& cpu);
void cs0(Cpu& cpu);
void goj1(Cpu& cpu);
void std2(Cpu& cpu);
void tc0(Cpu& cpu);
void tcf0(Cpu& cpu);
void ts0(Cpu& cpu);
void xch0(Cpu& cpu);

// Stage, Extend, BitMask, Opcode+QuarterCode, Name, Function
const static subinstruction subinstruction_list[] {
    {2, false, 000, 000, "STD2", std2},
    {0, false, 070, 000, "TC0", tc0},
    {1, false, 070, 000, "GOJ1", goj1},
    {0, false, 076, 010, "CCS0", ccs0},
    {0, false, 076, 011, "TCF0", tcf0},
    {0, false, 076, 012, "TCF0", tcf0},
    {0, false, 076, 013, "TCF0", tcf0},
    {0, false, 070, 030, "CA0", ca0},
    {0, false, 070, 040, "CS0", cs0},
    {0, false, 076, 054, "TS0", ts0},
    {0, false, 076, 056, "XCH0", xch0},
    {0, false, 070, 060, "AD0", ad0},
};
}
