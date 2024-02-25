#include "agc.hpp"

namespace agcplusplus::block2 {
    Cpu Agc::cpu;
    Memory Agc::memory;
    Scaler Agc::scaler;
    Timer Agc::timer;
    Cdu Agc::cdu;
    InitArguments Agc::config;
    std::ofstream Agc::log_stream;

Agc::Agc(const std::vector<word>& rope, const std::map<word, word>& padload, InitArguments init_args) {
    memory = Memory(MemoryInitState::BitsClear);
    config = init_args;

    // Set up log output stream.
    log_stream.open("AGCPlusPlus.log");

    for (const word& w : rope) {
        static int fixed_addr = 0;
        memory.write_fixed_word(fixed_addr++, w);
    }

    for (auto pair : padload) {
        memory.write_erasable_word(pair.first, pair.second);
    }
}

void Agc::run() {
    std::cout << "Computer started." << std::endl;
    cpu.start();
    timer.start();
}
}
