#include "globaldefs.hpp"
#include "cpu.hpp"
#include <functional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "control_pulses.cpp"

#pragma once

namespace agcplusplus {
void std2(Cpu& cpu);

const static std::vector<subinstruction> subinstruction_list {
    {2, false, 077, 000, "STD2", std2},
};
}
