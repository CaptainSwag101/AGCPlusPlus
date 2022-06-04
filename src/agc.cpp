#include "agc.hpp"
#include <chrono>

namespace agcplusplus {
Agc::Agc(std::array<word, SIZE_FIXED_MEM> rope, bool logMCT, bool logTimepulse) : cpu(logMCT, logTimepulse), memory(MemoryInitState::BitsClear), timer() {
    std::cout << "Initializing computer state..." << '\n';

    std::cout << "Loading rope into fixed memory...";
    for (word w : rope) {
        static int fixed_addr = 0;
        memory.write_fixed_word(fixed_addr++, w);
    }
    std::cout << " done!" << '\n';

    std::cout << "Assigning memory pointer for CPU...";
    cpu.assign_memory(memory);
    std::cout << " done!" << '\n';

    std::cout << "Assigning CPU pointer for timer...";
    timer.assign_cpu(cpu);
    std::cout << " done!\n";

    std::cout << "Assigning memory pointer for timer...";
    timer.assign_memory(memory);
    std::cout << " done!\n";

    std::cout << "Initializing computer state done." << '\n';
}

void Agc::run() {
    timer.start_timer();
}
}
