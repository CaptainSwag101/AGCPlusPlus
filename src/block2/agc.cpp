#include "agc.hpp"

namespace agcplusplus::block2 {
    Cpu Agc::cpu;
    Memory Agc::memory;
    Scaler Agc::scaler;
    Timer Agc::timer;
    InitArguments Agc::config;

Agc::Agc(const std::vector<word>& rope, const std::map<word, word>& padload, InitArguments init_args) {
    std::cout << "Initializing computer state..." << std::endl;

    memory = Memory(MemoryInitState::BitsClear);
    config = init_args;

    std::cout << "Loading rope into fixed memory...";
    for (const word& w : rope) {
        static int fixed_addr = 0;
        memory.write_fixed_word(fixed_addr++, w);
    }
    std::cout << " done!" << std::endl;

    std::cout << "Loading pad-loaded values into erasable memory...";
    for (auto pair : padload) {
        memory.write_erasable_word(pair.first, pair.second);
    }
    std::cout << " done!" << std::endl;

    std::cout << "Initializing computer state done." << std::endl;
}

void Agc::run() {
    cpu.start();
    timer.start();
}
}
