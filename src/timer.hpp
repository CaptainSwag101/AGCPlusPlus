#include "cpu.hpp"
#include "globaldefs.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include <chrono>
#include <thread>

#pragma once

namespace agcplusplus {
class Timer
{
public:
    Timer();
    void start_timer();
    void stop_timer();
    void assign_cpu(std::shared_ptr<Cpu> cpu);
    void assign_memory(std::shared_ptr<Memory> mem);
    void assign_scaler(std::shared_ptr<Scaler> scaler);

private:
    bool stop = false;

    std::shared_ptr<Cpu> cpu_ref;
    std::shared_ptr<Memory> memory_ref;
    std::shared_ptr<Scaler> scaler_ref;

    uint64_t total_ticks;

    // Timing variables for batching execution for timing accuracy
    constexpr static uint64_t TIMEPULSES_PER_SECOND = 1024000;
    constexpr static uint64_t TIMEPULSES_PER_MILLISECOND = TIMEPULSES_PER_SECOND / 1000;
};
}
