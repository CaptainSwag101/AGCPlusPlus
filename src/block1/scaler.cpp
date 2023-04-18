#include "scaler.hpp"

namespace agcplusplus::block1 {
    void Scaler::tick() {
        // Increment our ring counters
        previous_tick = current_tick;
        current_tick += 1;
    }
}