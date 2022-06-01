#include "cpu.hpp"
#include "subinstructions.hpp"

namespace agcplusplus {
Cpu::Cpu() {
    std::cout << "Initializing CPU..." << std::endl;

    z = 04000;
    current_subinstruction = subinstruction_list[0];

    std::cout << "Initializing CPU done." << std::endl;
}

void Cpu::assign_mem(Memory& mem) {
    memory = std::make_unique<Memory>(mem);
}



void Cpu::tick() {
    current_subinstruction.function(*this);
    print_state_info(std::cout);
    write_bus = 0;
    if (current_timepulse == 12) current_timepulse = 1;
    else ++current_timepulse;
}

void Cpu::print_state_info(std::ostream& output) const {
    output << current_subinstruction.name << " (T" << std::setw(2) << std::setfill('0') << (word)current_timepulse <<")" << std::endl;

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
    output << " ST = " << (word)st; // Cast from char to integer
    output << " BR = " << (br & 1) << ((br & 2) >> 1);
    output << " EB = " << std::setw(2) << std::setfill('0') << eb;
    output << " FB = " << std::setw(2) << std::setfill('0') << fb;
    output << " BB = " << std::setw(6) << std::setfill('0') << bb;
    output << std::endl;

    std::dec(output);
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

void Cpu::update_bb() {

}
}
