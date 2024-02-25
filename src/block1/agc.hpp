#pragma once

#include "block1defs.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "scaler.hpp"
#include "timer.hpp"
#include "sockpp/tcp_socket.h"

#include <fstream>
#include <memory>
#include <thread>

namespace agcplusplus::block1 {
    class Agc {
    public:
        static Timer timer;
        static Scaler scaler;
        static Memory memory;
        static Cpu cpu;
        static InitArguments configuration;
        static std::ofstream log_stream;

        Agc(std::vector<word> rope_buffer, InitArguments init_args);
        [[noreturn]] void run();

        [[noreturn]] void accept_dsky_connections();
        void process_dsky(sockpp::tcp_socket sock);
        std::array<uint8_t, 4> generate_dsky_packet(uint8_t channel, word data);
    };
}
