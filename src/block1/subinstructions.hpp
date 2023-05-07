#include "block1defs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus::block1 {
    // Subinstruction functions
    void ad0(Cpu& cpu);
    void ccs0(Cpu& cpu);
    void ccs1(Cpu& cpu);
    void cs0(Cpu& cpu);
    void msk0(Cpu& cpu);
    void ndx0(Cpu& cpu);
    void ndx1(Cpu& cpu);
    void std2(Cpu& cpu);
    void su0(Cpu& cpu);
    void tc0(Cpu& cpu);
    void ts0(Cpu& cpu);
    void xch0(Cpu& cpu);

    // Counter sequences
    void pinc(Cpu& cpu);
    void minc(Cpu& cpu);

    // Interrupt sequences

    // Subinstruction data array, ordered in the same way as in ND-1021041's table on page 4-121
    const static subinstruction subinstruction_data[] = {
            {"STD2", 2, false, 000, 000, std2},
            {"TC0", 0, false, 017, 000, tc0},
            {"XCH0", 0, false, 017, 003, xch0},
            {"CS0", 0, false, 017, 014, cs0},
            {"TS0", 0, false, 017, 015, ts0},
            {"MSK0", 0, false, 017, 017, msk0},
            {"AD0", 0, false, 017, 016, ad0},

            {"NDX0", 0, false, 017, 002, ndx0},
            {"NDX1", 1, false, 017, 002, ndx1},

            {"CCS0", 0, false, 017, 001, ccs0},
            {"CCS1", 1, false, 017, 001, ccs1},
            {"SU0", 0, true, 017, 013, su0},
    };

    const static subinstruction sub_pinc = {
            "PINC", 0, false, 000, 000, pinc
    };
    const static subinstruction sub_minc = {
            "MINC", 0, false, 000, 000, minc
    };
    const static subinstruction sub_rupt0 = {

    };
}
