#include "globaldefs.hpp"
#include "cpu.hpp"

#include "control_pulses.cpp"

#pragma once

namespace agcplusplus {
void ad0(Cpu& cpu);
void bzf0(Cpu& cpu);
void ca0(Cpu& cpu);
void ccs0(Cpu& cpu);
void cs0(Cpu& cpu);
void goj1(Cpu& cpu);
void ndx0(Cpu& cpu);
void ndx1(Cpu& cpu);
void qxch0(Cpu& cpu);
void std2(Cpu& cpu);
void tc0(Cpu& cpu);
void tcf0(Cpu& cpu);
void ts0(Cpu& cpu);
void wand0(Cpu& cpu);
void xch0(Cpu& cpu);

// Stage, Extend, BitMask, Opcode+QuarterCode, Name, Function
const static subinstruction subinstruction_list[] {
    {2, false, 000, 000, "STD2", std2},
    {0, false, 070, 000, "TC0", tc0},
    {1, false, 070, 000, "GOJ1", goj1},
    {0, false, 076, 010, "CCS0", ccs0},
    {0, false, 076, 012, "TCF0", tcf0},
    {0, false, 076, 014, "TCF0", tcf0},
    {0, false, 076, 016, "TCF0", tcf0},
    {0, false, 070, 030, "CA0", ca0},
    {0, false, 070, 040, "CS0", cs0},
    {0, false, 076, 050, "NDX0", ndx0},
    {1, false, 076, 050, "NDX1", ndx1},
    {0, false, 076, 054, "TS0", ts0},
    {0, false, 076, 056, "XCH0", xch0},
    {0, false, 070, 060, "AD0", ad0},
    {0, true,  077, 003, "WAND0", wand0},
    {0, true,  076, 012, "BZF0", bzf0},
    {0, true,  076, 014, "BZF0", bzf0},
    {0, true,  076, 016, "BZF0", bzf0},
    {0, true,  076, 022, "QXCH0", qxch0},
    {2, true,  000, 000, "STD2", std2}, // Catch-all
};
}
