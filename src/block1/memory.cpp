#include "memory.hpp"

namespace agcplusplus::block1 {

    word Memory::read(word address, word bank) {
        if (address <= MEM_ERASABLE_END) {
            word temp = erasable[address];
            erasable[address] = 0;  // Erasable reads are destructive
            temp |= (temp & BITMASK_16) >> 1;   // Copy bit 16 (SG) into bit 15 (US)
            //temp &= ~BITMASK_16;    // Mask out SG
            return temp;
        } else {
            int32_t fixed_addr = address - 02000;
            fixed_addr |= ((bank - 1) << 12);

            word temp = fixed[fixed_addr];
            temp |= (temp & BITMASK_16) >> 1;   // Copy bit 16 (SG) into bit 15 (US)
            //temp &= ~BITMASK_16;    // Mask out SG

            return temp;
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