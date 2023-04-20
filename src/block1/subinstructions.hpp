#include "block1defs.hpp"
#include "cpu.hpp"

#include <functional>
#include <string>

#pragma once

namespace agcplusplus::block1 {
    // Subinstruction functions
    void std2(Cpu& cpu);

    // Subinstruction data array
    const static subinstruction subinstruction_data[] = {
            {"STD2", 2, false, 000, 000, std2},
    };
}
