#include "agc.hpp"

namespace agcplusplus::block1 {
    Timer Agc::timer;
    Scaler Agc::scaler;
    Memory Agc::memory;
    Cpu Agc::cpu;
    std::thread dsky_thread;

    void Agc::run() {
        timer.start();

        while (true) {
            timer.execute_tick_batch();
        }
    }
}