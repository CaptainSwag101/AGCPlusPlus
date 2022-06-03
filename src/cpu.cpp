#include "cpu.hpp"
#include "subinstructions.hpp"

namespace agcplusplus {
Cpu::Cpu(bool logMCT, bool logTimepulse) {
    std::cout << "Initializing CPU..." << '\n';

    if (logTimepulse) verbosity = LoggingVerbosity::CpuStatePerTimepulse;
    else if (logMCT) verbosity = LoggingVerbosity::CpuStatePerMCT;
    else verbosity = LoggingVerbosity::None;

    current_subinstruction = subinstruction_list[2];    // Inject GOJ1 (GOJAM) to init computer for startup

    std::cout << "Initializing CPU done." << '\n';
}

void Cpu::assign_mem(Memory& mem) {
    memory = std::make_unique<Memory>(mem);
}

void Cpu::tick() {
    // At the start of every timepulse, clear MCRO
    mcro = false;

    // Before pulse 1, do INKBT1
    if (current_timepulse == 1) {
        // TODO: Add INKL handling once we fully implement I/O
        if (st != 2) {
            fetch_next_instruction = false;
            extend_next = false;
        }
    }

    // Before T2, T5, T8, and T11, reset PIFL
    if (current_timepulse == 2 || current_timepulse == 5 || current_timepulse == 8 || current_timepulse == 11) {
        pifl = false;
    }

    // Actually execute the portion of the current subinstruction for the current timepulse
    current_subinstruction.function(*this);

    // Memory reads are done after T4
    if (current_timepulse == 4) {
        // Determine whether we are targeting fixed or erasable memory
        if (s < MEM_ERASABLE_END) {    // Erasable memory
            if (s >= 010) {
                s_temp = s; // Preserve S in case it's changed before the writeback
                word erasable_addr = get_erasable_absolute_addr();
                g = memory->read_erasable_word(erasable_addr);
            }
        } else {    // Fixed memory
            // Don't read from fixed memory during division steps 3, 7, 6, or 4.
            // Based on SBF being inhibited by hardware logic during those phases.
            if (!dv) {  // TODO: Implement gray-code check
                word fixed_addr = get_fixed_absolute_addr();
                g = memory->read_fixed_word(fixed_addr);
            }
        }
    }

    // Memory writebacks are done after T9 if we performed an erasable read
    if (current_timepulse == 9 && s_temp > 0) {
        memory->write_erasable_word(s_temp, g);
        s_temp = 0;
    }

    // Print CPU state information before we clear the write bus
    if ((verbosity == LoggingVerbosity::CpuStatePerMCT && current_timepulse == 1) || verbosity == LoggingVerbosity::CpuStatePerTimepulse) {
        print_state_info(std::cout);
    }

    // Clear the write bus after every timepulse
    write_bus = 0;

    // Perform cleanup and fetch the next subinstruction if needed after T12 (or T3 during division)
    if ((!dv && current_timepulse == 12) || (dv && current_timepulse == 3)) {
        st = st_next;
        st_next = 0;

        if (fetch_next_instruction) {
            sq = (b & BITMASK_10_14) >> 9;  // B10-14 to SQ1-5
            sq |= (b & BITMASK_16) >> 10;   // B16 to SQ6
            extend = extend_next;
        }

        // Populate current_subinstruction based on the contents of SQ, ST, and EXTEND
        bool found_implemented_subinstruction = false;
        for (auto& subinst : subinstruction_list) {
            if (extend == subinst.sequence_extend && st == subinst.stage && (sq & subinst.sequence_mask) == subinst.sequence_opcode) {
                current_subinstruction = subinst;
                found_implemented_subinstruction = true;
                break;
            }
        }

        if (!found_implemented_subinstruction) {
            std::oct(std::cout);
            std::cout << "Unimplemented subinstruction at Z = " << std::setw(6) << std::setfill('0') << z << ", replacing with STD2.\n";
            std::dec(std::cout);
            current_subinstruction = subinstruction_list[0];    // Force STD2
            s = z;  // Reset the location we read the next instruction data from
        }
    }

    // Increment or reset timepulse count
    if (current_timepulse == 12) {
        current_timepulse = 1;
    } else {
        ++current_timepulse;
    }
}

void Cpu::print_state_info(std::ostream& output) const {
    output << current_subinstruction.name << " (T" << std::setw(2) << std::setfill('0') << (word)current_timepulse <<")" << '\n';

    std::oct(output);

    output << " A = " << std::setw(6) << a;
    output << " L = " << std::setw(6) << l;
    output << " G = " << std::setw(6) << g;
    output << " B = " << std::setw(6) << b;
    output << " Z = " << std::setw(6) << z;
    output << " Q = " << std::setw(6) << q;
    output << '\n';

    output << " S = " << std::setw(6) << s;
    output << " SQ = " << std::setw(2) << sq;
    output << " ST = " << (word)st; // Cast from char to integer
    output << " BR = " << (br & 1) << ((br & 2) >> 1);
    output << " EB = " << std::setw(2) << (eb >> 8);
    output << " FB = " << std::setw(2) << (fb >> 11);
    output << " BB = " << std::setw(6) << bb;
    output << '\n';

    output << " EXTEND = " << (word)extend;
    output << " INHINT = " << (word)inhibit_interrupts;
    output << " X = " << std::setw(6) << x;
    output << " Y = " << std::setw(6) << y;
    output << " U = " << std::setw(6) << u;
    output << " WL = " << std::setw(6) << write_bus;
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
    bb = fb | (eb >> 8);
}

void Cpu::update_eb_fb() {
    eb = (bb & 7) << 8;
    fb = bb & BITMASK_11_15;
}

word Cpu::get_erasable_absolute_addr() const {
    word abs_addr = 0;

    if (s >= MEM_ERASABLE_BANKED_START && s <= MEM_ERASABLE_BANKED_END) {
        abs_addr = s & 0377;
        abs_addr |= eb;
    } else {
        abs_addr = s;
    }

    return abs_addr;
}

word Cpu::get_fixed_absolute_addr() const {
    word abs_addr = 0;

    if (s >= MEM_FIXED_BANKED_START && s <= MEM_FIXED_BANKED_END) {
        abs_addr = s & 01777;
        abs_addr |= fb;
    } else {
        abs_addr = s;
    }

    return abs_addr;
}
}
