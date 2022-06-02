#include "globaldefs.hpp"
#include "cpu.hpp"

#include "control_pulses.cpp"

#pragma once

namespace agcplusplus {
void ca0(Cpu& cpu);
void ccs0(Cpu& cpu);
void cs0(Cpu& cpu);
void goj1(Cpu& cpu);
void std2(Cpu& cpu);
void tc0(Cpu& cpu);
void ts0(Cpu& cpu);

// Stage, Extend, BitMask, Opcode+QuarterCode, Name, Function
const static subinstruction subinstruction_list[] {
    {2, false, 000, 000, "STD2", std2},
    {0, false, 070, 000, "TC0", tc0},
    {1, false, 070, 000, "GOJ1", goj1},
    {0, false, 076, 010, "CCS0", ccs0},
    {0, false, 070, 030, "CA0", ca0},
    {0, false, 070, 040, "CS0", cs0},
    {0, false, 076, 054, "TS0", ts0},
};
}
