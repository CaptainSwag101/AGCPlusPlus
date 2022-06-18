#include "cpu.hpp"
#include "subinstructions.hpp"

namespace agcplusplus {
Cpu::Cpu(bool logMCT, bool logTimepulse) {
    std::cout << "Initializing CPU..." << std::endl;

    if (logTimepulse) verbosity = LoggingVerbosity::CpuStatePerTimepulse;
    else if (logMCT) verbosity = LoggingVerbosity::CpuStatePerMCT;
    else verbosity = LoggingVerbosity::None;

    // Prepare I/O channels
    std::cout << "Initializing I/O channels...";
    io_channels.emplace(010, 0);
    io_channels.emplace(011, 0);
    io_channels.emplace(012, 0);
    io_channels.emplace(015, 0);
    io_channels.emplace(016, 0);
    std::cout << " done!" << std::endl;

    // Perform GOJAM to initialize state
    gojam();

    std::cout << "Initializing CPU done." << std::endl;
}

void Cpu::assign_memory(std::shared_ptr<Memory> mem) {
    memory = mem;
}

void Cpu::tick() {
    // At the start of every timepulse, clear MCRO
    mcro = false;

    // Before pulse 1, do INKBT1
    if (current_timepulse == 1) {
        // Service INKL
        if (inkl) {
            // Remember what we wanted to do, so we can come back to it later
            pending_subinstruction = current_subinstruction;

            for (int c = 0; c < 20; ++c) {
                if (counters[c] & COUNT_DIRECTION_UP) {
                    if (c >= COUNTER_TIME2 && c <= COUNTER_TIME5) {
                        current_subinstruction = COUNT_SUBINST_PINC;
                    }
                    break;
                }

            }
        }

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
            // Check for pending counter requests
            bool prev_inkl = inkl;
            inkl = false;
            for (word w : counters) {
                if (w != COUNT_DIRECTION_NONE && !sudo) {
                    inkl = true;
                    break;
                }
            }

            // If no counters need servicing and we have a pending subinstruction, get back to it.
            if (!inkl && prev_inkl) {
                current_subinstruction = pending_subinstruction;
            }

            // Check for pending interrupts
            bool should_rupt = false;
            interrupt_being_serviced = 0177777; // -0 to indicate no interrupt being actively serviced
            for (int r = 0; r < 11; ++r) {
                if (interrupts[r] == true) {
                    should_rupt = true;
                    interrupt_being_serviced = r;
                    switch (r) {
                    case RUPT_KEYRUPT1:
                        std::cout << "KEYRUPT1 triggered" << std::endl;
                        break;
                    }

                    break;
                }
            }

            uint8_t a_signs = (a & BITMASK_15_16) >> 14;
            bool a_overflow = (a_signs == 0b01 || a_signs == 0b10);
            if (should_rupt && !inhibit_interrupts && !iip && !extend_next && !sudo && !a_overflow) {
                subinstruction rupt0 = RUPT_SUBINST_RUPT0;
                sq = rupt0.sequence_opcode;
                extend = rupt0.sequence_extend;
            } else {
                sq = (b & BITMASK_10_14) >> 9;  // B10-14 to SQ1-5
                sq |= (b & BITMASK_16) >> 10;   // B16 to SQ6
                extend = extend_next;
            }
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
            std::cout << "Unimplemented subinstruction, replacing with STD2." << std::endl;
            print_state_info(std::cout);

            subinstruction std2 = subinstruction_list[0];
            current_subinstruction = std2;
            s = z & BITMASK_1_12;
        }
    }

    // Increment or reset timepulse count
    if (current_timepulse == 12) {
        current_timepulse = 1;
    } else {
        ++current_timepulse;
    }
}

void Cpu::gojam() {
    current_subinstruction = subinstruction_list[2];    // Inject GOJ1 (GOJAM) to init computer for startup
    sq = 0;
    extend = false;
    extend_next = false;
    st = 1;
    st_next = 1;
    br = 0;
    restart = true;
}

void Cpu::print_state_info(std::ostream& output) const {
    std::dec(output);

    output << current_subinstruction.name << " (T" << std::setw(2) << std::setfill('0') << (word)current_timepulse <<")" << std::endl;

    std::oct(output);

    output << " A = " << std::setw(6) << a;
    output << " L = " << std::setw(6) << l;
    output << " G = " << std::setw(6) << g;
    output << " B = " << std::setw(6) << b;
    output << " Q = " << std::setw(6) << q;
    output << " Z = " << std::setw(6) << z;
    output << '\n';

    output << " S = " << std::setw(6) << s;
    output << " SQ = " << std::setw(2) << sq;
    output << " ST = " << (word)st; // Cast from char to integer
    output << " BR = " << (br & 1) << ((br & 2) >> 1);
    output << " EB = " << std::setw(2) << (eb >> 8);
    output << " FB = " << std::setw(2) << (fb >> 10);
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

word Cpu::read_io_channel(word address) {
    word result;

    switch (address) {
    case 1:
        result = l;
        break;
    case 2:
        result = q;
        break;
    default:
        result = io_channels[address] & ~BITMASK_16;    // Mask out bit 16, since erasable words are only 15 bits wide
        result |= ((result & BITMASK_15) << 1);   // Copy bit 15 into bit 16
        break;
    }

    return result;
}

void Cpu::write_io_channel(word address, word data) {
    switch (address) {
    case 1:
        l = data;
        break;
    case 2:
        q = data;
        break;
    default:
        word temp = data & ~BITMASK_15; // Mask out bit 15
        temp |= ((temp & BITMASK_16) >> 1); // Copy bit 16 into bit 15
        temp &= ~BITMASK_16;    // Mask out bit 16 since erasable words are only 15 bits wide
        io_channels[address] = temp;
        break;
    }
}
}
