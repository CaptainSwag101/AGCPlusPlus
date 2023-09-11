#include "agc.hpp"

namespace agcplusplus::block2 {
    Cpu Agc::cpu;
    Memory Agc::memory;
    Scaler Agc::scaler;
    Timer Agc::timer;
    InitArguments Agc::config;
    Logger Agc::logger;

Agc::Agc(const std::vector<word>& rope, const std::map<word, word>& padload, const InitArguments& init_args) {
    memory = Memory(MemoryInitState::BitsClear);
    config = init_args;

    // Set up logger
    logger.initialize_database("log.db3", init_args);
    logger.initialize_cpu_table(std::string("'Subinstruction' TEXT, 'Timepulse' INTEGER, 'A' TEXT, 'L' TEXT, 'Q' TEXT, 'Z' TEXT, 'G' TEXT, 'B' TEXT, 'S' TEXT, 'SQ' TEXT, 'ST' TEXT, 'BR' TEXT, 'EB' TEXT, 'FB' TEXT, 'BB' TEXT, 'FEXT' TEXT, 'EXTEND' INTEGER, 'INHINT' INTEGER, 'IIP' INTEGER, 'INKL' INTEGER, 'X' TEXT, 'Y' TEXT, 'U' TEXT, 'WL' TEXT"));

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
