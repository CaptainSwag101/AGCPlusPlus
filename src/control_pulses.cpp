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

static void nisq(Cpu& cpu) {
    cpu.fetch_next_instruction = true;
    cpu.inhibit_interrupts = false;
    // TODO: Permit increments from counters when implemented
}

static void ra(Cpu& cpu) {
    cpu.write_bus |= cpu.a;
}

static void rad(Cpu& cpu) {
    switch (cpu.g)
    {
    case 3:     // RELINT
        cpu.inhibit_interrupts = false;
        rz(cpu);
        st2(cpu);
        break;
    case 4:     // INHINT
        cpu.inhibit_interrupts = true;
        rz(cpu);
        st2(cpu);
        break;
    case 6:     // EXTEND
        cpu.extend_next = true;
        rz(cpu);
        st2(cpu);
        break;
    default:    // ANYTHING ELSE
        rg(cpu);
        break;
    }
}

static void rb(Cpu& cpu) {
    cpu.write_bus |= cpu.b;
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
        cpu.write_bus |= cpu.io_channels[cpu.s & 077];  // TODO: Copy bit 16 to 15
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

static void rq(Cpu& cpu) {
    cpu.write_bus |= cpu.q;
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

static void ru(Cpu& cpu) {
    cpu.write_bus |= cpu.u;
}

static void rz(Cpu& cpu) {
    cpu.write_bus |= cpu.z;
}

static void st2(Cpu& cpu) {
    cpu.st_next |= 2;
}

static void wa(Cpu& cpu) {
    cpu.a = cpu.write_bus;
}

static void wb(Cpu& cpu) {
    cpu.b = cpu.write_bus;
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
            cpu.g = (cpu.write_bus & 0b0011111110000000) >> 7;
            break;
        }
    }
    else
    {
        cpu.g = cpu.write_bus;
    }
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
            cpu.eb = cpu.write_bus;
            cpu.update_bb();
            break;
        case 4:
            cpu.fb = cpu.write_bus;
            cpu.update_bb();
            break;
        case 5:
            cpu.z = cpu.write_bus;
            break;
        case 6:
            cpu.bb = cpu.write_bus;
            break;
    };
}

static void wy(Cpu& cpu) {
    cpu.explicit_carry = false;
    cpu.x = 0;
    cpu.y = cpu.write_bus;
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
}
