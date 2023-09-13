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
    void start();

private:
    void accept_dsky_connections();
    void process_dsky(sockpp::tcp_socket sock);
    static void commit_log_transactions();
    std::array<uint8_t, 4> generate_dsky_packet(uint8_t channel, word data);

    uint64_t total_ticks = 0;

    // Timing variables for batching execution for timing accuracy
    constexpr static uint64_t TIMEPULSES_PER_SECOND = 1024000;
    constexpr static uint64_t TIMEPULSES_PER_MILLISECOND = TIMEPULSES_PER_SECOND / 1000;
};
}
