#include "control_pulses.hpp"

namespace agcplusplus::block1 {
    void ci(Cpu& cpu) {
        cpu.carry_in = true;
        cpu.update_adder();
    }

    void gp(Cpu& cpu) {
        // TODO
    }

    void nisq(Cpu& cpu) {
        cpu.fetch_next_subinstruction = true;
    }

    void rb(Cpu& cpu) {
        cpu.write_bus |= cpu.b;
    }

    void rg(Cpu& cpu) {
        cpu.write_bus |= cpu.g;
    }

    void rsc(Cpu& cpu) {
        // Determine central register to read from based on contents of S register
        switch (cpu.s) {
            case 0:
                cpu.write_bus |= cpu.a;
                break;
            case 1:
                cpu.write_bus |= cpu.q;
                break;
            case 2:
                cpu.write_bus |= cpu.z;
                break;
            case 3:
                cpu.write_bus |= cpu.lp;
                break;
            case 015:
                cpu.write_bus |= cpu.bank;
                break;
        }
    }

    void ru(Cpu& cpu) {
        cpu.write_bus |= cpu.u;
    }

    void rz(Cpu& cpu) {
        cpu.write_bus |= cpu.z;
    }

    void tp(Cpu& cpu) {
        // TODO
    }

    void wb(Cpu &cpu) {
        cpu.b = cpu.write_bus;
    }

    void wg(Cpu& cpu) {
        word temp = cpu.write_bus;

        word s_correct = (cpu.s_temp > 0) ? cpu.s_temp : cpu.s;

        if (s_correct >= 020 && s_correct <= 023) {
            switch (s_correct) {
                case 020:   // Cycle Right
                {
                    word bottom_to_top = (cpu.write_bus & 1) << 15; // Cycle bit 1 to bit 16
                    temp = ((cpu.write_bus & ~BITMASK_15_16) >> 1) | bottom_to_top;    // Mask out bits 15 and 16 before shifting so they are blank afterwards
                    temp |= ((cpu.write_bus & BITMASK_16) >> 2);  // Copy the old bit 16 into bit 14
                    break;
                }
                case 021:   // Shift Right
                {
                    word top_bit = (cpu.write_bus & BITMASK_16);    // Remember bit 16
                    temp = ((cpu.write_bus & ~BITMASK_15_16) >> 1) | top_bit;  // Mask out bits 15 and 16 before shifting so they are blank afterwards
                    temp |= ((cpu.write_bus & BITMASK_16) >> 2);  // Copy the old bit 16 into bit 14
                    break;
                }
                case 022:   // Cycle Left
                {
                    word top_to_bottom = (cpu.write_bus & BITMASK_16) >> 15; // Cycle the most significant bit to the least
                    word new_top = ((cpu.write_bus & BITMASK_14) << 2); // Remember bit 14 and double-shift it so it ends up in bit 16
                    temp = ((cpu.write_bus & ~BITMASK_14_15) << 1) | top_to_bottom | new_top;  // Mask out bits 14 and 15 before shifting so they are blank afterwards
                    break;
                }
                case 023:  // EDOP, move 7 bits right
                {
                    temp = ((cpu.write_bus & BITMASK_8_14) >> 7);
                    break;
                }
            }
        }

        cpu.g = temp;
    }

    void wp(Cpu& cpu) {
        // TODO
    }

    void ws(Cpu& cpu) {
        cpu.s = cpu.write_bus;
    }

    void wsc(Cpu& cpu) {
        // Determine central register to write to based on contents of S register
        switch (cpu.s) {
            case 0:
                cpu.a = cpu.write_bus;
                break;
            case 1:
                cpu.q = cpu.write_bus;
                break;
            case 2:
                cpu.z = cpu.write_bus;
                break;
            case 3:
                cpu.lp = cpu.write_bus;
                break;
            case 015:
                cpu.bank = cpu.write_bus;
                break;
        }
    }

    void wy(Cpu& cpu) {
        cpu.carry_in = false;
        cpu.y = cpu.write_bus;
        cpu.update_adder();
    }

    void wz(Cpu& cpu) {
        cpu.z = cpu.write_bus;
    }
}