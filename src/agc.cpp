#include "agc.hpp"

namespace agcplusplus {
Agc::Agc() : cpu(), memory(MemoryInitState::Random) {
    std::cout << "Initializing computer state..." << std::endl;

    std::cout << "Assigning memory pointer for CPU...";
    cpu.assign_mem(memory);
    std::cout << " done!" << std::endl;

    std::cout << "Initializing computer state done." << std::endl;
}

void Agc::run() {
    int64_t totalTicks = 0;
    while (totalTicks <= 120) {
        // Perform MCT
        for (uint8_t t = 1; t <= 12; ++t) {
            cpu.tick();
            ++totalTicks;
        }
    }
}
}
