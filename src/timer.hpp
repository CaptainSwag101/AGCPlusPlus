#include "cpu.hpp"
#include "globaldefs.hpp"
#include "memory.hpp"
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
    void assign_cpu(Cpu& cpu);
    void assign_memory(Memory& mem);

private:
    bool stop = false;

    std::shared_ptr<Cpu> cpu_ref;
    std::shared_ptr<Memory> memory_ref;

    uint64_t total_ticks;
};
}
