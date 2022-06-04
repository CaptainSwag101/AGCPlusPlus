#include "memory.hpp"

namespace agcplusplus {
Memory::Memory(MemoryInitState initState) {
    std::cout << "Initializing memory..." << std::endl;

    // Seed the RNG
    random_seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::cout << "Random seed set to " << random_seed << "." << std::endl;
    rand_gen = std::minstd_rand(random_seed);

    // Populate erasable memory with desired data pattern
    for (uint64_t i = 0; i < SIZE_ERASABLE_MEM; ++i) {
        if (initState == MemoryInitState::BitsClear) {
            erasable[i] = 0;
        } else if (initState == MemoryInitState::BitsSet) {
            erasable[i] = 0177777;
        } else {
            erasable[i] = static_cast<word>(rand_gen());
        }
    }

    // Populate fixed memory with desired data pattern
    for (uint64_t i = 0; i < SIZE_FIXED_MEM; ++i) {
        if (initState == MemoryInitState::BitsClear) {
            fixed[i] = 0;
        } else if (initState == MemoryInitState::BitsSet) {
            fixed[i] = 0177777;
        } else {
            fixed[i] = static_cast<word>(rand_gen());
        }
    }

    std::cout << "Initializing memory done." << std::endl;
}

word Memory::read_erasable_word(word address) {
    word temp = erasable[address] & ~BITMASK_15;    // Mask out bit 15
    temp |= (temp & BITMASK_16) >> 1;   // Copy bit 16 into bit 15
    erasable[address] = 0;
    return temp;
}

word Memory::read_fixed_word(word address) const {
    word temp = fixed[address] & ~BITMASK_15;   // Mask out bit 15
    temp |= (temp & BITMASK_16) >> 1;   // Copy bit 16 into bit 15
    return temp;
}

void Memory::write_erasable_word(word address, word data) {
    erasable[address] = data;
}

void Memory::write_fixed_word(word address, word data) {
    fixed[address] = data;
}
}
