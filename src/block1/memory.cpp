#include "memory.hpp"

namespace agcplusplus::block1 {

    word Memory::read(word address, word bank) {
        if (address <= MEM_ERASABLE_END) {
            word temp = erasable[address];
            erasable[address] = 0;  // Erasable reads are destructive
            return temp;
        } else {
            int32_t fixed_addr = 0;
            if (address <= MEM_FIXED_FIXED_END) {
                fixed_addr = address - MEM_FIXED_FIXED_START;
            } else {
                fixed_addr = address - MEM_FIXED_BANKED_START;
                fixed_addr += (bank - 1) * MEM_FIXED_BANKED_SIZE;
            }

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