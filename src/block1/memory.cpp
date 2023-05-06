#include "memory.hpp"

namespace agcplusplus::block1 {

    word Memory::read(word address, word bank) {
        if (address <= MEM_ERASABLE_END) {
            // Return zero when accessing central and system registers
            if (address < 020) return 0;

            word temp = erasable[address];
            erasable[address] = 0;  // Erasable reads are destructive
            return temp;
        } else if (address <= MEM_FIXED_BANKED_END) {
            uint32_t fixed_addr = 0;
            if (address <= MEM_FIXED_FIXED_END) {
                fixed_addr = address - MEM_FIXED_FIXED_START;
            } else {
                fixed_addr = address - MEM_FIXED_BANKED_START;
                fixed_addr += (bank - 1) * MEM_FIXED_BANKED_SIZE;
            }

            return fixed[fixed_addr];
        } else {
            std::cout << "Invalid memory access attempt at " << std::oct << address << "." << std::dec << std::endl;
            return 0;
        }
    }

    void Memory::write(word address, word data) {
        if (address >= 020 && address <= MEM_ERASABLE_END) {
            erasable[address] = data;
        }
    }

    void Memory::assign_fixed_memory(std::vector<word> buffer) {
        for (int i = 0; i < std::min(buffer.size(), fixed.size()); ++i) {
            fixed[i] = buffer[i];
        }
    }
}