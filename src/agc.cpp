#include "agc.hpp"
#include <chrono>

namespace agcplusplus {
Agc::Agc(std::array<word, SIZE_FIXED_MEM> rope, bool logMCT, bool logTimepulse) {
    std::cout << "Initializing computer state..." << std::endl;

    cpu = std::make_shared<Cpu>(logMCT, logTimepulse);
    memory = std::make_shared<Memory>(MemoryInitState::BitsClear);
    scaler = std::make_shared<Scaler>();
    timer = std::make_shared<Timer>();

    std::cout << "Loading rope into fixed memory...";
    for (word w : rope) {
        static int fixed_addr = 0;
        memory->write_fixed_word(fixed_addr++, w);
    }
    std::cout << " done!" << std::endl;

    std::cout << "Assigning memory pointer for CPU...";
    cpu->assign_memory(memory);
    std::cout << " done!" << std::endl;

    std::cout << "Assigning CPU pointer for timer...";
    timer->assign_cpu(cpu);
    std::cout << " done!" << std::endl;

    std::cout << "Assigning memory pointer for timer...";
    timer->assign_memory(memory);
    std::cout << " done!" << std::endl;

    std::cout << "Assigning CPU pointer for scaler...";
    scaler->assign_cpu(cpu);
    std::cout << " done!" << std::endl;

    std::cout << "Assigning scaler pointer for timer...";
    timer->assign_scaler(scaler);
    std::cout << " done!" << std::endl;

    std::cout << "Initializing computer state done." << std::endl;
}

void Agc::run() {
    timer->start_timer();
}
}
