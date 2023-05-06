#include "control_pulses.hpp"
#include "../common/util_functions.hpp"

namespace agcplusplus::block1 {
    void ci(Cpu& cpu) {
        cpu.carry_in = true;
        cpu.update_adder();
    }

    void gp(Cpu& cpu) {
        // TODO
    }

    void nisq(Cpu& cpu) {
        cpu.fetch_new_subinstruction = true;
    }

    void ra(Cpu& cpu) {
        cpu.write_bus |= cpu.a;
    }

    void rb(Cpu& cpu) {
        cpu.write_bus |= cpu.b;
    }

    void rc(Cpu& cpu) {
        cpu.write_bus |= ~(cpu.b);
    }

    void rg(Cpu& cpu) {
        word temp = cpu.g;
        temp &= ~BITMASK_15;    // Mask out bit 15 (US)
        temp |= (temp & BITMASK_16) >> 1;   // Copy bit 16 (SG) into bit 15 (US)
        cpu.write_bus |= temp;
    }

    void rq(Cpu& cpu) {
        cpu.write_bus |= cpu.q;
    }

    void rp2(Cpu& cpu) {
        // TODO
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
                cpu.write_bus |= (cpu.bank << 10);
                break;
        }
    }

    void ru(Cpu& cpu) {
        cpu.write_bus |= cpu.u;
    }

    void rz(Cpu& cpu) {
        cpu.write_bus |= cpu.z;
    }

    void r1(Cpu& cpu) {
        cpu.write_bus |= 1;
    }

    void r1c(Cpu& cpu) {
        cpu.write_bus |= 017776;
    }

    void r2(Cpu& cpu) {
        cpu.write_bus |= 2;
    }

    void r22(Cpu& cpu) {
        cpu.write_bus |= 022;
    }

    void r24(Cpu& cpu) {
        cpu.write_bus |= 024;
    }

    void st1(Cpu& cpu) {
        cpu.st_next |= 1;
    }

    void st2(Cpu& cpu) {
        cpu.st_next |= 2;
    }

    void tmz(Cpu& cpu) {
        if (cpu.write_bus == 0177777) {
            cpu.br |= 0b01; // Set LSB (BR 2) if -0 is on the write bus.
        }
    }

    void tov(Cpu& cpu) {
        word sign_bits = get_sign_bits(cpu.write_bus);
        //if (sign_bits == 0b01 || sign_bits == 0b10) {
            cpu.br = sign_bits; // Set MSB (BR 1) on negative overflow, LSB (BR 2) on positive overflow.
        //}
    }

    void tp(Cpu& cpu) {
        // TODO
    }

    void trsm(Cpu& cpu) {
        if (cpu.s == 025) {
            st2(cpu);
        }
    }

    void tsgn(Cpu& cpu) {
        if ((cpu.write_bus & BITMASK_15) > 0) {
            cpu.br |= 0b10; // Set MSB (BR 1) if sign bit is set
        }
    }

    void tsgn2(Cpu& cpu) {
        if ((cpu.write_bus & BITMASK_15) > 0) {
            cpu.br |= 0b01; // Set LSB (BR 2) if sign bit is set
        }
    }

    void wa(Cpu &cpu) {
        cpu.a = cpu.write_bus;
    }

    void wb(Cpu &cpu) {
        cpu.b = cpu.write_bus;
    }

    void wg(Cpu& cpu) {
        word temp = cpu.write_bus & ~BITMASK_15;    // Mask out bit 15 (US)

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

    void wovc(Cpu& cpu) {
        // TODO: Direct overflow to OVCTR priority inputs
    }

    void wovi(Cpu& cpu) {
        // If uncorrected sign and generated sign do not match, we have an overflow.
        word sign_bits = get_sign_bits(cpu.write_bus);
        if (sign_bits == 0b01 || sign_bits == 0b10) {
            cpu.inhibit_interrupts = true;
        }
    }

    void wp(Cpu& cpu) {
        // TODO
    }

    void wp2(Cpu& cpu) {
        // TODO
    }

    void wq(Cpu& cpu) {
        cpu.q = cpu.write_bus;
    }

    void ws(Cpu& cpu) {
        cpu.s = (cpu.write_bus & BITMASK_1_12);
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
                cpu.bank = (cpu.write_bus & BITMASK_11_15) >> 10;
                break;
        }
    }

    void wx(Cpu& cpu) {
        cpu.x |= cpu.write_bus;
        cpu.update_adder();
    }

    void wy(Cpu& cpu) {
        cpu.x = 0;
        cpu.y = cpu.write_bus;
        cpu.carry_in = false;
        cpu.update_adder();
    }

    void wz(Cpu& cpu) {
        cpu.z = cpu.write_bus;
    }
}