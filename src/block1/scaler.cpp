#include "scaler.hpp"

namespace agcplusplus::block1 {
    void Scaler::tick() {
        // Tick our divider stages
        previous_tick = current_tick;
        current_tick += 1;
    }
}