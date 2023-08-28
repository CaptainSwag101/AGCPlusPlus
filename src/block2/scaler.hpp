#include "block2defs.hpp"
#include "cpu.hpp"
#include <tuple>
#include <queue>

#pragma once

namespace agcplusplus::block2 {
class Scaler
{
public:
    explicit Scaler();
    void tick();
    void queue_dsky_update(word channel, word data);
    bool dsky_flash_state();
    void update_interrupt_state(bool new_iip);
    void signal_tc_started();
    void signal_tc_ended();

private:
    uint64_t cur_state = 0;
    uint64_t prev_state = 0;
    bool dsky_flash_on = false;
    bool interrupt_started = false;
    bool interrupt_ended = false;
    bool last_iip = false;
    bool tc_started = false;
    bool tc_ended = false;
    std::queue<std::tuple<word, word>> dsky_queue;
};
}
