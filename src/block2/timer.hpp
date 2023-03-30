#include "cpu.hpp"
#include "block2defs.hpp"
#include "memory.hpp"
#include "scaler.hpp"

#include "sockpp/tcp_acceptor.h"
#include "sockpp/socket.h"
#include <chrono>
#include <thread>

#pragma once

namespace agcplusplus::block2 {
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
    void accept_dsky_connections();
    void process_dsky(sockpp::tcp_socket sock);
    std::array<uint8_t, 4> generate_dsky_packet(uint8_t channel, word data);

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
