#include "globaldefs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus {
class Scaler
{
public:
    Scaler();
    void tick();
    void assign_cpu(std::shared_ptr<Cpu> cpu);

private:
    uint64_t cur_state;
    uint64_t prev_state;

    std::shared_ptr<Cpu> cpu_ref;
};
}
