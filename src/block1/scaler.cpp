#include "scaler.hpp"

namespace agcplusplus::block1 {
    void Scaler::tick() {
        // Increment our binary timing "layers"
        previous_tick = current_tick;
        current_tick += 1;
    }
}