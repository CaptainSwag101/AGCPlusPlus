#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include "globaldefs.hpp"

#pragma once

class Memory {
    enum class MemoryInitState {
        BitsClear,
        BitsSet,
        Random
    };

public:
    // Initializes the AGC's two sections of memory with the
    // specified initialization pattern.
    Memory(MemoryInitState initState = MemoryInitState::BitsClear);
    word read_fixed(word address) const;
    word read_erasable(word address) const;
    void write_fixed(word address, word data);
    void write_erasable(word address, word data);

    uint64_t random_seed;
    std::minstd_rand rand_gen;

private:
    static constexpr uint64_t FIXED_MEM_SIZE = 36864;
    static constexpr uint64_t ERASABLE_MEM_SIZE = 2048;

    std::array<word, FIXED_MEM_SIZE> fixed;
    std::array<word, ERASABLE_MEM_SIZE> erasable;
};
