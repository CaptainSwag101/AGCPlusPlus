#include "cpu.hpp"
#include "subinstructions.hpp"

namespace agcplusplus::block2 {
Cpu::Cpu(InitArguments init_args) {
    std::cout << "Initializing CPU..." << std::endl;

    if (init_args.log_timepulse) verbosity = LoggingVerbosity::CpuStatePerTimepulse;
    else if (init_args.log_mct) verbosity = LoggingVerbosity::CpuStatePerMCT;
    else verbosity = LoggingVerbosity::None;

    config = init_args;

    // Init CPU registers, counters, interrupts
    a = 0;
    b = 0;
    g = 0;
    l = 0;
    s = 0;
    s_temp = 0;
    no_eac = false;
    night_watchman = 0;
    sq = 0;
    st = 0;
    st_next = 0;
    br = 0;
    fext = 0;
    bb = 0;
    update_eb_fb();
    x = 0;
    y = 0;
    explicit_carry = false;
    update_adder();
    q = 0;
    z = 0;
    write_bus = 0;
    inhibit_interrupts = false;
    extend = false;
    extend_next = false;
    dv = false;
    dv_stage = 0;
    iip = false;
    pseudo = false;
    mcro = false;
    current_timepulse = 1;

    for (word &c : counters) {
        c = COUNT_DIRECTION_NONE;
    }

    for (bool &i : interrupts) {
        i = false;
    }

    // Assign workaround values for I/O channels 30-33,
    // which have an inverted state
    io_channels[030] = 0037777; // Set top bits low to remove TEMP light
    io_channels[031] = 0177777;
    io_channels[032] = 0177777;
    io_channels[033] = 0177777;

    // GOJAM to initialize state
    gojam();

    std::cout << "Initializing CPU done." << std::endl;
}

void Cpu::queue_gojam() {
    should_gojam = true;
}

void Cpu::gojam() {
    current_subinstruction = subinstruction_list[2];    // Inject GOJ1 (GOJAM) to init computer for startup
    sq = 0;
    extend = false;
    extend_next = false;
    st = 1;
    st_next = 0;
    restart = true;
    inkl = false;
    inhibit_interrupts = false;
    pseudo = false;
    no_eac = false;
    iip = false;
    should_gojam = false;

    // Clear channels 5, 6, 10-14, 34, 35, and 33 bit 11
    io_channels[005] = 0;
    io_channels[006] = 0;
    io_channels[010] = 0;
    io_channels[011] = 0;
    io_channels[012] = 0;
    io_channels[013] = 0;
    io_channels[014] = 0;
    io_channels[034] = 0;
    io_channels[035] = 0;
    io_channels[033] = io_channels[033] & ~BITMASK_11;

    // Clear all pending RUPTs
    for (bool &i : interrupts) {
        i = false;
    }
}

void Cpu::assign_memory(std::shared_ptr<Memory> mem) {
    memory = mem;
}

void Cpu::tick() {
    // At the run of every timepulse, clear MCRO
    mcro = false;


    // HACK: Reset I/O channel 33 to inverted state
    io_channels[033] = 0177777;


    // Before pulse 1, do INKBT1
    if (current_timepulse == 1) {
        // Service INKL
        if (inkl) {
            for (int c = 0; c < 20; ++c) {
                if (counters[c] & COUNT_DIRECTION_UP) {
                    if (c >= COUNTER_TIME2 && c <= COUNTER_TIME5) {
                        current_subinstruction = COUNT_SUBINST_PINC;
                        break;
                    }
                } else if (counters[c] & COUNT_DIRECTION_DOWN) {
                    if (c == COUNTER_TIME6) {
                        current_subinstruction = COUNT_SUBINST_DINC;
                        break;
                    }
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
        if (s <= MEM_ERASABLE_END) {    // Erasable memory
            if (s >= 010) {
                s_temp = s; // Preserve S in case it's changed before the writeback
                word erasable_addr = get_erasable_absolute_addr();
                g = memory->read_erasable_word(erasable_addr);
            }
        } else {    // Fixed memory
            // Don't read from fixed memory during division steps 3, 7, 6, or 4.
            // Based on SBF being inhibited by hardware logic during those phases.
            if (!dv || st < 3) {
                word fixed_addr = get_fixed_absolute_addr();
                // Check parity by reading raw value
                // Adapted from http://graphics.stanford.edu/~seander/bithacks.html#ParityMultiply
                word v = memory->read_fixed_word(fixed_addr, true);
                v ^= v >> 1;
                v ^= v >> 2;
                v = (v & 0x1111) * 0x1111;
                if ((((v >> 12) & 1) == 0) && !config.ignore_alarms) {    // Invalid parity
                    std::cout << "HARDWARE ALARM: FIXED MEMORY PARITY FAIL" << std::endl;
                    write_io_channel(077, 1);
                    queue_gojam();
                }
                g = memory->read_fixed_word(fixed_addr);
            }
        }
    }


    // Memory writebacks are done after T9 if we performed an erasable read
    if (current_timepulse == 9 && s_temp > 0) {
        // Preserve S but replace it so we can use get_erasable_absolute_addr()
        word s_temp2 = s;
        s = s_temp;
        memory->write_erasable_word(get_erasable_absolute_addr(), g);
        s = s_temp2;    // Restore S now that we've properly calculated the erasable address
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
        // Push stage to its next pending value
        st = st_next;
        st_next = 0;


        if (fetch_next_instruction) {
            // Check for pending counter requests
            bool prev_inkl = inkl;
            inkl = false;
            for (int c = 0; c < 20; ++c) {
                if (counters[c] != COUNT_DIRECTION_NONE && !pseudo && !config.ignore_counters) {
                    inkl = true;
                    break;
                }
            }


            // Check for pending interrupts
            bool rupt_pending = false;
            for (int r = 0; r < 11; ++r) {
                if (interrupts[r] == true) {
                    rupt_pending = true;
                    break;
                }
            }


            uint8_t a_signs = (a & BITMASK_15_16) >> 14;
            bool a_overflow = (a_signs == 0b01 || a_signs == 0b10);
            if (rupt_pending && !config.ignore_interrupts && !inhibit_interrupts && !iip && !extend_next && !pseudo && !a_overflow) {
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


        // If a GOJAM is pending, perform it, overriding all else
        if (should_gojam) {
            gojam();
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
    output << " FEXT = " << (word)((fext & 0160) >> 4);
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

word Cpu::get_erasable_absolute_addr() {
    word abs_addr = 0;

    if (s >= MEM_ERASABLE_BANKED_START && s <= MEM_ERASABLE_BANKED_END) {
        abs_addr = s & 0377;
        abs_addr |= eb;
    } else {
        abs_addr = s;
    }

    // If address being read/written is 67, signal the night watchman
    if (abs_addr == 067) {
        night_watchman = true;
    }

    return abs_addr;
}

word Cpu::get_fixed_absolute_addr() const {
    word abs_addr = 0;

    if (s >= MEM_FIXED_BANKED_START && s <= MEM_FIXED_BANKED_END) {
        abs_addr = s & 01777;
        // Check if we're superbanking
        if (((fext >> 4) >= 4) && (fb >= 060000)) { // Yes, superbank
            abs_addr |= (fb & 0016000); // Mask out the top two bits of FB
            abs_addr |= (fext << 9);    // Put FEXT's three bits over the top two bits and extend
        } else {    // No, not superbank
            abs_addr |= fb;
        }
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
    case 7:
        result = fext;
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
    case 7:
        fext = (data & 0160);
        //std::cout << "FEXT changed to " << (word)(fext >> 4) << std::endl;
        // Fall through
    default:
        word temp = data & ~BITMASK_15; // Mask out bit 15
        temp |= ((temp & BITMASK_16) >> 1); // Copy bit 16 into bit 15
        temp &= ~BITMASK_16;    // Mask out bit 16 since erasable words are only 15 bits wide
        io_channels[address] = temp;
        break;
    }
}
}
