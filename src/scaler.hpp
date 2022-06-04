#include "globaldefs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus {
class Scaler
{
public:
    Scaler();
    void assign_cpu(Cpu& cpu);
    void tick();

private:
    uint64_t cur_state;
    uint64_t prev_state;

    std::shared_ptr<Cpu> cpu_ref;
};
}
