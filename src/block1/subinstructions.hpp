#include "block1defs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus::block1 {
    // Subinstruction functions
    void cs0(Cpu& cpu);
    void std2(Cpu& cpu);
    void tc0(Cpu& cpu);
    void ts0(Cpu& cpu);
    void xch0(Cpu& cpu);

    // Subinstruction data array
    const static subinstruction subinstruction_data[] = {
            {"STD2", 2, false, 000, 000, std2},
            {"TC0", 0, false, 017, 000, tc0},
            {"XCH0", 0, false, 017, 003, xch0},
            {"CS0", 0, false, 017, 004, cs0},
            {"TS0", 0, false, 017, 011, ts0},
    };
}
