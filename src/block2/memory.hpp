#pragma once

#include <array>
#include "block2defs.hpp"

namespace agcplusplus::block2 {
enum class MemoryInitState {
    BitsClear,
    BitsSet,
    Random
};

class Memory {
public:
    // Initializes the AGC's two sections of memory with the
    // specified initialization pattern.
    explicit Memory(MemoryInitState initState = MemoryInitState::BitsClear);
    word read_fixed_word(word address, bool raw_parity = false) const;
    word read_erasable_word(word address);
    void write_fixed_word(word address, word data);
    void write_erasable_word(word address, word data);

private:
    std::array<word, SIZE_FIXED_MEM> fixed{};
    std::array<word, SIZE_ERASABLE_MEM> erasable{};
};
}
