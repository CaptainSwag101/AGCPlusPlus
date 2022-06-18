#include "globaldefs.hpp"
#include "cpu.hpp"
#include <tuple>
#include <queue>

#pragma once

namespace agcplusplus {
class Scaler
{
public:
    Scaler();
    void tick();
    void assign_cpu(std::shared_ptr<Cpu> cpu);
    void queue_dsky_update(word channel, word data);
    bool dsky_flash_state();

private:
    uint64_t cur_state;
    uint64_t prev_state;
    bool dsky_flash_on = false;

    std::queue<std::tuple<word, word>> dsky_queue;

    std::shared_ptr<Cpu> cpu_ref;
};
}
