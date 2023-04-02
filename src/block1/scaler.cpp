#include "scaler.hpp"

namespace agcplusplus::block1 {
    void Scaler::start() {
        state = ComponentState::Started;
    }

    void Scaler::stop() {
        state = ComponentState::Stopped;
    }

    void Scaler::single_step() {
        state = ComponentState::Started;
        tick();
        state = ComponentState::Stopped;
    }

    void Scaler::tick() {
        if (state != ComponentState::Started) return;

        // Increment our ring counters
        previous_tick = current_tick;
        current_tick += 1;
    }
}