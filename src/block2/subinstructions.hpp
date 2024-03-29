#include "block2defs.hpp"
#include "cpu.hpp"

#include "control_pulses.cpp"

#pragma once

namespace agcplusplus::block2 {
void ad0(Cpu& cpu);
void ads0(Cpu& cpu);
void aug0(Cpu& cpu);
void bzf0(Cpu& cpu);
void bzmf0(Cpu& cpu);
void ca0(Cpu& cpu);
void ccs0(Cpu& cpu);
void cs0(Cpu& cpu);
void das0(Cpu& cpu);
void das1(Cpu& cpu);
void dca0(Cpu& cpu);
void dca1(Cpu& cpu);
void dcs0(Cpu& cpu);
void dcs1(Cpu& cpu);
void dim0(Cpu& cpu);
void dinc(Cpu& cpu);
void dv0(Cpu& cpu);
void dv1(Cpu& cpu);
void dv3(Cpu& cpu);
void dv7(Cpu& cpu);
void dv6(Cpu& cpu);
void dv4(Cpu& cpu);
void dxch0(Cpu& cpu);
void dxch1(Cpu& cpu);
void goj1(Cpu& cpu);
void incr0(Cpu& cpu);
void lxch0(Cpu& cpu);
void mp0(Cpu& cpu);
void mp1(Cpu& cpu);
void mp3(Cpu& cpu);
void msk0(Cpu& cpu);
void msu0(Cpu& cpu);
void ndx0(Cpu& cpu);
void ndx1(Cpu& cpu);
void ndxx0(Cpu& cpu);
void ndxx1(Cpu& cpu);
void pinc(Cpu& cpu);
void qxch0(Cpu& cpu);
void rand0(Cpu& cpu);
void read0(Cpu& cpu);
void ror0(Cpu& cpu);
void rsm3(Cpu& cpu);
void rxor0(Cpu& cpu);
void rupt0(Cpu& cpu);
void rupt1(Cpu& cpu);
void std2(Cpu& cpu);
void su0(Cpu& cpu);
void tc0(Cpu& cpu);
void tcf0(Cpu& cpu);
void ts0(Cpu& cpu);
void wand0(Cpu& cpu);
void wor0(Cpu& cpu);
void write0(Cpu& cpu);
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
    {0, false, 076, 020, "DAS0", das0},
    {1, false, 076, 020, "DAS1", das1},
    {0, false, 076, 022, "LXCH0", lxch0},
    {0, false, 076, 024, "INCR0", incr0},
    {0, false, 076, 026, "ADS0", ads0},
    {0, false, 070, 030, "CA0", ca0},
    {0, false, 070, 040, "CS0", cs0},
    {0, false, 076, 050, "NDX0", ndx0},
    {1, false, 076, 050, "NDX1", ndx1},
    {3, false, 076, 050, "RSM3", rsm3},
    {0, false, 076, 052, "DXCH0", dxch0},
    {1, false, 076, 052, "DXCH1", dxch1},
    {0, false, 076, 054, "TS0", ts0},
    {0, false, 076, 056, "XCH0", xch0},
    {0, false, 070, 060, "AD0", ad0},
    {0, false, 070, 070, "MSK0", msk0},
    {0, true,  077, 000, "READ0", read0},
    {0, true,  077, 001, "WRITE0", write0},
    {0, true,  077, 002, "RAND0", rand0},
    {0, true,  077, 003, "WAND0", wand0},
    {0, true,  077, 004, "ROR0", ror0},
    {0, true,  077, 005, "WOR0", wor0},
    {0, true,  077, 006, "RXOR0", rxor0},
    {0, true,  077, 007, "RUPT0", rupt0},
    {1, true,  077, 007, "RUPT1", rupt1},
    {0, true,  076, 010, "DV0", dv0},
    {1, true,  076, 010, "DV1", dv1},
    {3, true,  076, 010, "DV3", dv3},
    {7, true,  076, 010, "DV7", dv7},
    {6, true,  076, 010, "DV6", dv6},
    {4, true,  076, 010, "DV4", dv4},
    {0, true,  076, 012, "BZF0", bzf0},
    {0, true,  076, 014, "BZF0", bzf0},
    {0, true,  076, 016, "BZF0", bzf0},
    {0, true,  076, 020, "MSU0", msu0},
    {0, true,  076, 022, "QXCH0", qxch0},
    {0, true,  076, 024, "AUG0", aug0},
    {0, true,  076, 026, "DIM0", dim0},
    {0, true,  070, 030, "DCA0", dca0},
    {1, true,  070, 030, "DCA1", dca1},
    {0, true,  070, 040, "DCS0", dcs0},
    {1, true,  070, 040, "DCS1", dcs1},
    {0, true,  070, 050, "NDXX0", ndxx0},
    {1, true,  070, 050, "NDXX1", ndxx1},
    {0, true,  076, 060, "SU0", su0},
    {0, true,  076, 062, "BZMF0", bzmf0},
    {0, true,  076, 064, "BZMF0", bzmf0},
    {0, true,  076, 066, "BZMF0", bzmf0},
    {0, true,  070, 070, "MP0", mp0},
    {1, true,  070, 070, "MP1", mp1},
    {3, true,  070, 070, "MP3", mp3},
    {2, true,  000, 000, "STD2", std2}, // Catch-all
};

const static subinstruction RUPT_SUBINST_RUPT0
    {0, true,  077, 007, "RUPT0", rupt0};

const static subinstruction COUNT_SUBINST_PINC
    {0, false, 000, 000, "PINC", pinc};

const static subinstruction COUNT_SUBINST_DINC
    {0, false, 000, 000, "DINC", dinc};
}
