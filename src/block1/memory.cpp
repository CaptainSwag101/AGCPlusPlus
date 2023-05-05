#include "memory.hpp"

namespace agcplusplus::block1 {

    word Memory::read(word address, word bank) {
        if (address <= MEM_ERASABLE_END) {
            return erasable[address];
        } else {
            int32_t fixed_addr = address - 02000;
            fixed_addr |= ((bank - 1) << 12);
            return fixed[fixed_addr];
        }
    }

    void Memory::write(word address, word bank, word data) {

    }

    void Memory::assign_fixed_memory(std::vector<word> buffer) {
        for (int i = 0; i < std::min(buffer.size(), fixed.size()); ++i) {
            fixed[i] = buffer[i];
        }
    }
}