#include "cpu.hpp"

namespace agcplusplus {
Cpu::Cpu() {
    std::cout << "Initializing CPU..." << std::endl;

    std::cout << "Initializing CPU done." << std::endl;
}

void Cpu::assign_mem(Memory& mem) {
    memory = std::make_unique<Memory>(mem);
}

void Cpu::tick() {

}

void Cpu::update_adder()
{
    // Basic addition step
    uint32_t temp = x + y;

    // Handle carries
    uint32_t carry = ci ? 1 : 0;        // Explicit carry
    if (!no_eac)
        carry |= ((temp >> 16) & 1);    // End-around carry if not inhibited
    temp += carry;

    u = (word)temp;
}
}
