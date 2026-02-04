#include "memory.hpp"

#include <chrono>
#include <random>

namespace agcplusplus::block2 {
Memory::Memory(const MemoryInitState initState) {
    // Populate erasable memory with desired data pattern
    if (initState == MemoryInitState::BitsClear) {
        erasable.fill(0);
    } else if (initState == MemoryInitState::BitsSet) {
        erasable.fill(0177777);
    } else {
        // Seed the RNG
        const auto seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
        const uint64_t random_seed = seconds_since_epoch.count();
        auto rand_gen = std::minstd_rand(random_seed);
        for (uint64_t i = 0; i < SIZE_ERASABLE_MEM; ++i) {
            erasable[i] = static_cast<word>(rand_gen());
        }
    }

    // Always fill fixed memory's empty space with zero.
    fixed.fill(0);
}

word Memory::read_erasable_word(word address) {
    // Special case for address 7, which is hard-wired to 0.
    if (address == 7) return 0;

    word temp = erasable[address] & ~BITMASK_16;    // Mask out bit 16, since erasable words are only 15 bits wide
    temp |= ((temp & BITMASK_15) << 1);   // Copy bit 15 into bit 16
    erasable[address] = 0;  // Erasable reads are destructive
    return temp;
}

word Memory::read_fixed_word(word address, bool raw_parity) const {
    if (raw_parity) {
        return fixed[address];
    }

    word temp = fixed[address] & ~BITMASK_15;   // Mask out bit 15
    temp |= (temp & BITMASK_16) >> 1;   // Copy bit 16 into bit 15
    return temp;
}

void Memory::write_erasable_word(word address, word data) {
    // Discard values written to address 7 because it should always be 0.
    if (address == 7) return;

    word temp = data & ~BITMASK_15; // Mask out bit 15
    temp |= ((temp & BITMASK_16) >> 1); // Copy bit 16 into bit 15
    temp &= ~BITMASK_16;    // Mask out bit 16 since erasable words are only 15 bits wide
    erasable[address] = temp;
}

void Memory::write_fixed_word(word address, word data) {
    fixed[address] = data;
}
}
