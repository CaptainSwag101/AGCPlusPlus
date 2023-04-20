#include "cpu.hpp"
#include "agc.hpp"

namespace agcplusplus::block1 {
    void Cpu::tick() {
        process_before_timepulse();
        process_timepulse();
        process_after_timepulse();
    }

    void Cpu::process_before_timepulse() {
        // Data arrives from memory at T6, rather than T4 on Block II.
        if (timepulse == 6) {
            g = Agc::memory.read(s, bank);
        }
    }

    void Cpu::process_timepulse() {

    }

    void Cpu::process_after_timepulse() {
        // Increment/reset timepulse count
        if (timepulse < 12) {
            ++timepulse;
        } else {
            timepulse = 1;
        }
    }
}