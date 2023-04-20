#include "agc.hpp"
#include "subinstructions.hpp"

namespace agcplusplus::block1 {
    Timer Agc::timer;
    Scaler Agc::scaler;
    Memory Agc::memory;
    Cpu Agc::cpu;
    std::thread dsky_thread;

    [[noreturn]] void Agc::run() {
        timer.start();
        cpu.current_subinstruction = subinstruction_data[0];

        while (true) {
            timer.execute_tick_batch();
        }
    }
}