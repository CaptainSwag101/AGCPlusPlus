#include "memory.hpp"
#include "agc.hpp"

namespace agcplusplus::block1 {

    word Memory::read(word address, word bank) {
        word data = 0;

        std::cout << std::setfill('0');

        if (address <= MEM_ERASABLE_END) {
            // Return zero when accessing central and system registers
            if (address < 020) return 0;

            data = erasable[address];
            data &= ~BITMASK_15;    // Mask out parity bit
            data |= (data & BITMASK_16) >> 1;   // Copy bit 16 into bit 15
            erasable[address] = 0;  // Erasable reads are destructive
            if (Agc::configuration.log_memory) {
                std::cout << "Read from erasable memory: " << std::oct << std::setw(4) << address;
                std::cout << ": " << std::setw(6) << data << std::dec << std::endl;
            }
        } else if (address <= MEM_FIXED_BANKED_END) {
            uint32_t fixed_addr;
            if (address <= MEM_FIXED_FIXED_END) {
                fixed_addr = address - MEM_FIXED_FIXED_START;
            } else if (bank > 0) {
                fixed_addr = address - MEM_FIXED_BANKED_START;
                fixed_addr += (bank - 1) * MEM_FIXED_BANKED_SIZE;
            } else {
                std::cout << "Invalid fixed-banked memory read: " << std::oct << std::setw(2) << bank << "," << std::setw(4) << address;
                std::cout << ": " << std::setw(6) << data << std::dec << std::endl;
            }

            data = fixed[fixed_addr];
            data &= ~BITMASK_15;    // Mask out parity bit
            data |= (data & BITMASK_16) >> 1;   // Copy bit 16 into bit 15
            if (Agc::configuration.log_memory) {
                std::cout << "Read from fixed memory: " << std::oct << std::setw(2) << bank << "," << std::setw(4) << address;
                std::cout << ": " << std::setw(6) << data << std::dec << std::endl;
            }
        } else {
            std::cout << "Invalid memory read: " << std::oct << std::setw(2) << bank << "," << std::setw(4) << address;
            std::cout << ": " << std::setw(6) << data << std::dec << std::endl;
        }

        return data;
    }

    void Memory::write(word address, word data) {
        if (address >= 020 && address <= MEM_ERASABLE_END) {
            data &= ~BITMASK_15;    // Mask out sign bit
            data |= (data & BITMASK_16) >> 1;   // Copy uncorrected sign into sign bit
            erasable[address] = data;
            if (Agc::configuration.log_memory) {
                std::cout << "Write to erasable memory: " << std::oct << std::setw(4) << address;
                std::cout << ": " << std::setw(6) << data << std::dec << std::endl;
            }
        }
    }

    void Memory::assign_fixed_memory(std::vector<word> buffer) {
        for (int i = 0; i < std::min<size_t>(buffer.size(), fixed.size()); ++i) {
            fixed[i] = buffer[i];
        }
    }
}