#include "block1defs.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include "sockpp/tcp_socket.h"
#include "../common/logger.h"

#include <memory>
#include <thread>

#pragma once

namespace agcplusplus::block1 {
    class Agc {
    public:
        static Timer timer;
        static Scaler scaler;
        static Memory memory;
        static Cpu cpu;
        static InitArguments configuration;
        static Logger logger;

        Agc(std::vector<word> rope_buffer, const InitArguments& init_args);
        [[noreturn]] void run();

        [[noreturn]] void accept_dsky_connections();
        void process_dsky(sockpp::tcp_socket sock);
        std::array<uint8_t, 4> generate_dsky_packet(uint8_t channel, word data);
    };
}
