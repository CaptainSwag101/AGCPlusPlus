#include "agc.hpp"
#include "subinstructions.hpp"

#include <utility>

namespace agcplusplus::block1 {
    Timer Agc::timer;
    Scaler Agc::scaler;
    Memory Agc::memory;
    Cpu Agc::cpu;
    std::thread Agc::dsky_thread;
    InitArguments Agc::configuration;

    Agc::Agc(std::vector<word> rope_buffer, InitArguments init_args) {
        memory.assign_fixed_memory(std::move(rope_buffer));
        configuration = init_args;
        cpu.go();
    }

    [[noreturn]] void Agc::run() {
        timer.start();
        cpu.current_subinstruction = subinstruction_data[0];

        while (true) {
            timer.execute_tick_batch();
        }
    }
}