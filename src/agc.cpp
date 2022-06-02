#include "agc.hpp"
#include <chrono>

namespace agcplusplus {
Agc::Agc(std::array<word, SIZE_FIXED_MEM> rope, bool verbose) : cpu(verbose), memory(MemoryInitState::BitsClear) {
    std::cout << "Initializing computer state..." << '\n';

    std::cout << "Loading rope into fixed memory...";
    for (word w : rope) {
        static int fixed_addr = 0;
        memory.write_fixed_word(fixed_addr++, w);
    }
    std::cout << " done!" << '\n';

    std::cout << "Assigning memory pointer for CPU...";
    cpu.assign_mem(memory);
    std::cout << " done!" << '\n';

    std::cout << "Initializing computer state done." << '\n';
}

void Agc::run() {
    int64_t totalTicks = 0;

    std::cout << "Target time per MCT: " << ((1.0 / (FREQUENCY_CPU / 12.0)) * 1000.0) << " milliseconds." << '\n';

    while (totalTicks <= 12 * 10) {
        // Perform MCT
        auto start = std::chrono::high_resolution_clock::now();
        for (uint8_t t = 1; t <= 12; ++t) {
            cpu.tick();
            ++totalTicks;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
        std::cout << "MCT completed in " << (duration / 1000000.0) << " milliseconds." << '\n';
    }
}
}
