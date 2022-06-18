#include "control_pulses.hpp"

namespace agcplusplus {
static void _8xp5(Cpu& cpu) {
    cpu.s |= 04000;
}

static void a2x(Cpu& cpu) {
    cpu.x = cpu.a;
    cpu.update_adder();
}

static void b15x(Cpu& cpu) {
    cpu.x |= 040000;
    cpu.update_adder();
}

static void ci(Cpu& cpu) {
    cpu.explicit_carry = true;
    cpu.update_adder();
}

static void clxc(Cpu& cpu) {
    if ((cpu.br & 0b10) == 0) {
        cpu.x = 0;
        cpu.update_adder();
    }
}

static void dvst(Cpu& cpu) {
    cpu.dv = true;
}

static void ext(Cpu& cpu) {
    cpu.extend_next = true;
}

static void g2ls(Cpu& cpu) {
    word temp = ((cpu.g & BITMASK_4_15) >> 3);
    temp |= (cpu.g & BITMASK_16);
    temp |= ((cpu.g & 1) << 14);

    cpu.l &= ~BITMASK_1_12;
    cpu.l &= ~BITMASK_15_16;
    cpu.l |= temp;
}

static void krpt(Cpu& cpu) {
    if (cpu.interrupt_being_serviced == 0177777) {
        std::cerr << "ERROR: Processing an interrupt when none were pending! Something has gone horribly wrong." << std::endl;
        return;
    }
    if (cpu.interrupts[cpu.interrupt_being_serviced] == false) {
        std::cerr << "WARNING: Attempting to service an inactive interrupt" << std::endl;
    }
    cpu.interrupts[cpu.interrupt_being_serviced] = false;
    cpu.iip = true;
}

static void l16(Cpu& cpu) {
    cpu.l |= BITMASK_16;
}

static void l2gd(Cpu& cpu) {
    cpu.g = ((cpu.l & BITMASK_1_14) << 1);  // L1-14 into G2-15
    cpu.g |= (cpu.l & BITMASK_16);  // L16 into G16
    cpu.g |= (cpu.mcro ? 1 : 0);    // MCRO into G1, bit 1 is cleared by the first step of this control pulse
}

static void monex(Cpu& cpu) {
    cpu.x |= 0177776;
    cpu.update_adder();
}

static void neacof(Cpu& cpu) {
    cpu.no_eac = false;
    cpu.update_adder();
}

static void neacon(Cpu& cpu) {
    cpu.no_eac = true;
    cpu.update_adder();
}

static void nisq(Cpu& cpu) {
    cpu.fetch_next_instruction = true;
    // TODO: This simply allows interrupts (if not inhibited) to occur
    // between whole instructions that would otherwise be prevented
    // between subinstructions of the same operation, i.e. between MP1 and MP3.
    //cpu.permit_interrupts = true;
    // TODO: Permit increments from counters when implemented
}

static void ponex(Cpu& cpu) {
    cpu.x |= 1;
    cpu.update_adder();
}

static void ptwox(Cpu& cpu) {
    cpu.x |= 2;
    cpu.update_adder();
}

static void r15(Cpu& cpu) {
    cpu.write_bus |= 0000015;
}

static void r1c(Cpu& cpu) {
    cpu.write_bus |= 0177776;
}

static void ra(Cpu& cpu) {
    cpu.write_bus |= cpu.a;
}

static void rad(Cpu& cpu) {
    switch (cpu.g)
    {
    case 3:     // RELINT
        cpu.inhibit_interrupts = false;
        cpu.sudo = true;
        rz(cpu);
        st2(cpu);
        break;
    case 4:     // INHINT
        cpu.inhibit_interrupts = true;
        cpu.sudo = true;
        rz(cpu);
        st2(cpu);
        break;
    case 6:     // EXTEND
        cpu.extend_next = true;
        cpu.sudo = true;
        rz(cpu);
        st2(cpu);
        break;
    default:    // ANYTHING ELSE
        cpu.sudo = false;
        rg(cpu);
        break;
    }
}

static void rb(Cpu& cpu) {
    cpu.write_bus |= cpu.b;
}

static void rb1(Cpu& cpu) {
    cpu.write_bus |= 1;
}

static void rb1f(Cpu& cpu) {
    if (cpu.br & 0b10) {
        cpu.write_bus |= 1;
    }
}

static void rb2(Cpu& cpu) {
    cpu.write_bus |= 2;
}

static void rc(Cpu& cpu) {
    cpu.write_bus |= (cpu.b ^ BITMASK_1_16);
}

static void rch(Cpu& cpu) {
    if (cpu.s == 1) {
        rl(cpu);
    } else if (cpu.s == 2) {
        rq(cpu);
    } else {
        cpu.write_bus |= cpu.read_io_channel(cpu.s & 077);
    }
}

static void rg(Cpu& cpu) {
    cpu.write_bus |= cpu.g;
}

static void rl(Cpu& cpu) {
    cpu.write_bus |= cpu.l & BITMASK_1_14;
    cpu.write_bus |= (cpu.l & BITMASK_16) >> 1;
    cpu.write_bus |= cpu.l & BITMASK_16;
}

static void rl10bb(Cpu& cpu) {
    cpu.write_bus |= cpu.b & BITMASK_1_10;
}

static void rq(Cpu& cpu) {
    cpu.write_bus |= cpu.q;
}

static void rrpa(Cpu& cpu) {
    for (int r = 0; r < 11; ++r) {
        if (cpu.interrupts[r] == true) {
            cpu.write_bus |= 04000 + (r * 4);   // Interrupt handlers located at octal 4000 + (4r)
            break;
        }
    }
}

static void rsc(Cpu& cpu) {
    switch (cpu.s) {
    case 0:
        ra(cpu);
        break;
    case 1:
        rl(cpu);
        break;
    case 2:
        rq(cpu);
        break;
    case 3:
        cpu.write_bus |= cpu.eb;
        break;
    case 4:
        cpu.write_bus |= cpu.fb;
        break;
    case 5:
        rz(cpu);
        break;
    case 6:
        cpu.write_bus |= cpu.bb;
        break;
    }
}

static void rsct(Cpu& cpu) {
    for (word c = 0; c < 20; ++c)
    {
        if (cpu.counters[c] != COUNT_DIRECTION_NONE) {
            cpu.write_bus |= c + 024;
            // Reset the counter request
            cpu.counters[c] = COUNT_DIRECTION_NONE;
            break;
        }
    }
}

static void rstrt(Cpu& cpu) {
    cpu.write_bus |= 04000;
}

static void ru(Cpu& cpu) {
    cpu.write_bus |= cpu.u;
}

static void rus(Cpu& cpu) {
    word temp = (cpu.u & BITMASK_1_14); // Bits 1-14 to 1-14
    temp |= (cpu.u & BITMASK_15);   // Bit 15 to 15
    temp |= ((cpu.u & BITMASK_15) << 1); // Bit 15 to 16
    cpu.write_bus |= temp;
}

static void rz(Cpu& cpu) {
    cpu.write_bus |= cpu.z;
}

static void st1(Cpu& cpu) {
    cpu.st_next |= 1;
}

static void st2(Cpu& cpu) {
    cpu.st_next |= 2;
}

static void tl15(Cpu& cpu) {
    cpu.br &= 0b01; // Mask out BR1
    cpu.br |= ((cpu.l & BITMASK_15) != 0) ? 0b10 : 0b00;
}

static void tmz(Cpu& cpu) {
    if (cpu.write_bus == 0177777) {
        cpu.br |= 0b01; // Set BR2 if -0
    } else {
        cpu.br &= 0b10; // Clear BR2 if not -0
    }
}

static void tov(Cpu& cpu) {
    switch ((cpu.write_bus & BITMASK_15_16) >> 14) {
    case 0b01:
        cpu.br = 0b01;
        break;
    case 0b10:
        cpu.br = 0b10;
        break;
    default:
        cpu.br = 0b00;
        break;
    }
}

static void tpzg(Cpu& cpu) {
    if (cpu.g == 0) {
        cpu.br |= 0b01; // Set BR2
    }
}

static void trsm(Cpu& cpu) {
    if (cpu.s == 017) {
        st2(cpu);
    }
}

static void tsgn(Cpu& cpu) {
    cpu.br &= 0b01; // BR1 is bit 2, mask it clear
    cpu.br |= ((cpu.write_bus & BITMASK_16) ? 0b10 : 0b00);
}

static void tsgn2(Cpu& cpu) {
    cpu.br &= 0b10; // BR2 is bit 1, mask it clear
    cpu.br |= ((cpu.write_bus & BITMASK_16) ? 0b01 : 0b00);
}

static void wa(Cpu& cpu) {
    cpu.a = cpu.write_bus;
}

static void wals(Cpu& cpu) {
    word a_temp = (cpu.write_bus >> 2);
    if ((cpu.g & 1) != 0) {
        a_temp |= ((cpu.g & BITMASK_16) >> 1);
        a_temp |= (cpu.g & BITMASK_16);
    } else {
        a_temp |= ((cpu.write_bus & BITMASK_16) >> 1);
        a_temp |= (cpu.write_bus & BITMASK_16);
    }
    cpu.a = a_temp;

    word l_temp = ((cpu.write_bus & BITMASK_1_2) << 12);
    cpu.l &= ~BITMASK_1_2;
    cpu.l |= l_temp;
}

static void wb(Cpu& cpu) {
    cpu.b = cpu.write_bus;
}

static void wch(Cpu& cpu) {
    if (cpu.s == 1) {
        wl(cpu);
    } else if (cpu.s == 2) {
        wq(cpu);
    } else {
        word temp = cpu.write_bus & ~BITMASK_15;    // Mask out bit 15
        temp |= (cpu.write_bus & BITMASK_16) >> 1;  // Bit 16 into bit 15
        cpu.write_io_channel(cpu.s & 077, temp);
    }
}

static void wg(Cpu& cpu) {
    if (cpu.s >= 020 && cpu.s <= 023) {
        switch (cpu.s) {
        case 020:   // Cycle Right
            word bottom_to_top;
            bottom_to_top = cpu.write_bus << 15;    // Cycle the least significant bit to the most
            cpu.g = (cpu.write_bus >> 1) | bottom_to_top;
            break;
        case 021:   // Shift Right
            word top_bit;
            top_bit = cpu.write_bus & BITMASK_16;
            cpu.g = (cpu.write_bus >> 1) | top_bit;  // Shift right, preserving top bit
            break;
        case 022:   // Cycle Left
            word top_to_bottom;
            top_to_bottom = (cpu.write_bus & 1) >> 15; // Cycle the most significant bit to the least
            cpu.g = (cpu.write_bus << 1) | top_to_bottom;
            break;
        case 023:  // EDOP, move 7 bits right
            cpu.g = (cpu.write_bus & BITMASK_8_14) >> 7;
            break;
        }
    }
    else
    {
        cpu.g = cpu.write_bus;
    }
}

static void wl(Cpu& cpu) {
    cpu.l = cpu.write_bus;
}

static void wovr(Cpu& cpu) {
    // Check for positive overflow on the counters
    if (((cpu.write_bus & BITMASK_15_16) >> 14) == 0b01)
    {
        switch (cpu.s - 024) {
        case COUNTER_TIME1:
            cpu.counters[COUNTER_TIME2] |= COUNT_DIRECTION_UP;
            break;
        case COUNTER_TIME3:
            cpu.interrupts[RUPT_T3RUPT] = true;
            break;
        case COUNTER_TIME4:
            cpu.interrupts[RUPT_T4RUPT] = true;
            break;
        case COUNTER_TIME5:
            cpu.interrupts[RUPT_T5RUPT] = true;
            break;
        }
    }
}

static void wq(Cpu& cpu) {
    cpu.q = cpu.write_bus;
}

static void ws(Cpu& cpu) {
    cpu.s = cpu.write_bus & BITMASK_1_12;
}

static void wsc(Cpu& cpu) {
    switch (cpu.s) {
        case 0:
            cpu.a = cpu.write_bus;
            break;
        case 1:
            cpu.l = cpu.write_bus;
            break;
        case 2:
            cpu.q = cpu.write_bus;
            break;
        case 3:
            cpu.eb = (cpu.write_bus & BITMASK_8_10);
            cpu.update_bb();
            break;
        case 4:
            cpu.fb = (cpu.write_bus & BITMASK_11_15);
            cpu.update_bb();
            break;
        case 5:
            cpu.z = cpu.write_bus;
            break;
        case 6:
            cpu.bb = cpu.write_bus;
            cpu.update_eb_fb();
            break;
    };
}

static void wy(Cpu& cpu) {
    cpu.explicit_carry = false;
    cpu.x = 0;
    cpu.y = cpu.write_bus;
    cpu.update_adder();
}

static void wyd(Cpu& cpu) {
    cpu.explicit_carry = false;
    cpu.x = 0;
    cpu.y = ((cpu.write_bus & BITMASK_1_14) << 1);  // WL1-14 into Y2-15
    cpu.y |= (cpu.write_bus & BITMASK_16);  // WL16 into Y16
    // WL16 into Y1 if circumstances allow
    if (!cpu.no_eac && !cpu.shinc && !(cpu.pifl && ((cpu.l & BITMASK_15) != 0))) {
        cpu.y |= ((cpu.write_bus & BITMASK_16) >> 15);
    }
    cpu.update_adder();
}

static void wy12(Cpu& cpu) {
    cpu.explicit_carry = false;
    cpu.x = 0;
    cpu.y = cpu.write_bus & BITMASK_1_12;
    cpu.update_adder();
}

static void wz(Cpu& cpu) {
    cpu.z = cpu.write_bus;
}

static void zap(Cpu& cpu) {
    ru(cpu);
    g2ls(cpu);
    wals(cpu);
}

static void zip(Cpu& cpu) {
    // Do complicated state stuff first
    word state_bits;
    state_bits |= (((cpu.l >> 14) & 1) << 2);   // L bit 15 into state bit 3
    state_bits |= (cpu.l & 3);                  // L bits 1,2 into state bits 1,2

    // Clear MCRO, it will be re-set if necessary below
    cpu.mcro = false;
    switch (state_bits) {
    case 0b000:
        wy(cpu);
        break;
    case 0b001:
        rb(cpu);
        wy(cpu);
        break;
    case 0b010:
        rb(cpu);
        wyd(cpu);
        break;
    case 0b011:
        rc(cpu);
        wy(cpu);
        ci(cpu);
        cpu.mcro = true;
        break;
    case 0b100:
        rb(cpu);
        wy(cpu);
        break;
    case 0b101:
        rb(cpu);
        wyd(cpu);
        break;
    case 0b110:
        rc(cpu);
        wy(cpu);
        ci(cpu);
        cpu.mcro = true;
        break;
    case 0b111:
        wy(cpu);
        cpu.mcro = true;
        break;
    }

    a2x(cpu);
    l2gd(cpu);
}
}
