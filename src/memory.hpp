#include <array>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>

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
    uint16_t read_fixed(uint16_t address) const;
    uint16_t write_erasable(uint16_t address) const;
    void write_fixed(uint16_t address, uint16_t word);
    void write_erasable(uint16_t address, uint16_t word);

    uint64_t random_seed;
    std::minstd_rand rand_gen;

private:
    static constexpr uint64_t FIXED_MEM_SIZE = 36864;
    static constexpr uint64_t ERASABLE_MEM_SIZE = 2048;

    std::array<uint16_t, FIXED_MEM_SIZE> fixed;
    std::array<uint16_t, ERASABLE_MEM_SIZE> erasable;
};
