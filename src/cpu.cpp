#include "cpu.hpp"
#include "control_pulses.hpp"

namespace agcplusplus {
Cpu::Cpu() {
    std::cout << "Initializing CPU..." << std::endl;

    std::cout << "Initializing CPU done." << std::endl;
}

void Cpu::assign_mem(Memory& mem) {
    memory = std::make_unique<Memory>(mem);
}

void Cpu::print_state_info(std::ostream& output) const {
    std::oct(output);
    output << " A = " << std::setw(6) << std::setfill('0') << a;
    output << " L = " << std::setw(6) << std::setfill('0') << l;
    output << " G = " << std::setw(6) << std::setfill('0') << g;
    output << " B = " << std::setw(6) << std::setfill('0') << b;
    output << " Z = " << std::setw(6) << std::setfill('0') << z;
    output << " Q = " << std::setw(6) << std::setfill('0') << q;
    output << std::endl;

    output << " S = " << std::setw(6) << std::setfill('0') << s;
    output << " SQ = " << std::setw(2) << std::setfill('0') << sq;
    output << " ST = " << st;
    output << " BR = " << (br & 1) << ((br & 2) >> 1);
    output << " EB = " << std::setw(2) << std::setfill('0') << eb;
    output << " FB = " << std::setw(2) << std::setfill('0') << fb;
    output << " BB = " << std::setw(6) << std::setfill('0') << bb;
    output << std::endl;

    std::dec(output);
}

void Cpu::tick() {
    a = memory->rand_gen();
    a2x(*this);
}

void Cpu::update_adder()
{
    // Basic addition step
    uint32_t temp = x + y;

    // Handle carries
    uint32_t carry = explicit_carry ? 1 : 0;    // Explicit carry
    if (!no_eac)
        carry |= ((temp >> 16) & 1);    // End-around carry if not inhibited
    temp += carry;

    u = (word)temp;
}
}
