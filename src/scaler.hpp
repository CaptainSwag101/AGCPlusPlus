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
    void update_interrupt_state(bool new_iip);

private:
    uint64_t cur_state = 0;
    uint64_t prev_state = 0;
    bool dsky_flash_on = false;
    bool interrupt_started = false;
    bool interrupt_ended = false;
    bool last_iip = false;
    std::queue<std::tuple<word, word>> dsky_queue;
    std::shared_ptr<Cpu> cpu_ref;
};
}
