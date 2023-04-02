#include "agc.hpp"

namespace agcplusplus::block1 {
    Timer Agc::timer;
    Scaler Agc::scaler;
    Memory Agc::memory;

    [[noreturn]] void Agc::run() {
        timer.start();
        scaler.start();

        while (true) {
            timer.execute_tick_batch();
        }
    }
}