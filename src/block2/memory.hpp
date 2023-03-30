#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include "globaldefs.hpp"

#pragma once

namespace agcplusplus {
enum class MemoryInitState {
    BitsClear,
    BitsSet,
    Random
};

class Memory {
public:
    // Initializes the AGC's two sections of memory with the
    // specified initialization pattern.
    Memory(MemoryInitState initState = MemoryInitState::BitsClear);
    word read_fixed_word(word address, bool raw_parity = false) const;
    word read_erasable_word(word address);
    void write_fixed_word(word address, word data);
    void write_erasable_word(word address, word data);

    uint64_t random_seed;
    std::minstd_rand rand_gen;

private:
    std::array<word, SIZE_FIXED_MEM> fixed;
    std::array<word, SIZE_ERASABLE_MEM> erasable;
};
}
