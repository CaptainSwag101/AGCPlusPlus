#include "control_pulses.hpp"
#include "../common/util_functions.hpp"

namespace agcplusplus::block1 {
    word _cycle_right(const word input) {
        word temp;
        word bottom_bit = input & 1;
        word top_bit = input & BITMASK_16;
        temp = (input & ~BITMASK_15_16) >> 1; // Mask out bits 15 and 16 before shifting so they are blank afterwards
        temp |= bottom_bit << 15;   // Cycle bit 1 into bit 16
        temp |= top_bit >> 2;   // Shift the old bit 16 into bit 14
        return temp;
    }
    word _cycle_right_lp(const word input) {
        word temp;
        word bottom_bit = input & 1;
        word top_bit = input & BITMASK_16;
        temp = (input & ~BITMASK_15_16) >> 1; // Mask out bits 15 and 16 before shifting so they are blank afterwards
        temp |= bottom_bit << 15;   // Cycle bit 1 into bit 16
        temp |= bottom_bit << 14;   // Cycle bit 1 into bit 15
        // Don't copy old bit 16 into bit 14
        return temp;
    }

    word _shift_right(const word input) {
        word temp;
        word top_bit = input & BITMASK_16;  // Remember bit 16
        temp = input >> 1;  // Shift right 1 bit
        temp |= top_bit;    // Restore bit 16
        return temp;
    }

    word _cycle_left(const word input) {
        word temp;
        word top_to_bottom = (input & BITMASK_16) >> 15;    // Cycle the most significant bit to the least
        word new_top = ((input & BITMASK_14) << 2); // Remember bit 14 and double-shift it so it ends up in bit 16
        temp = ((input & ~BITMASK_14_15) << 1) | top_to_bottom | new_top;   // Mask out bits 14 and 15 before shifting so they are blank afterwards
        return temp;
    }

    word _shift_left(const word input) {
        word temp;
        word top_bit = input & BITMASK_16;
        temp = (input & ~BITMASK_14_15) << 1;   // Mask out bits 14 and 15 so they don't interfere. Bit 16 is discarded.
        temp |= top_bit;    // Restore bit 16 after the shift discarded it
        temp |= (top_bit >> 15);    // Bit 16 also goes into bit 1
        return temp;
    }

    void ci(Cpu& cpu) {
        cpu.carry_in = true;
        cpu.update_adder();
    }

    void clg(Cpu& cpu) {
        cpu.g = 0;
    }

    void ctr(Cpu& cpu) {
        if (cpu.multiply_counter == 0) {
            st2(cpu);   // Set stage 2 when MP1 loop is complete (6 repetitions)
        } else {
            cpu.multiply_counter--;
        }
    }

    void gp(Cpu& cpu) {
        // TODO
    }

    void krpt(Cpu& cpu) {
        word rupt_address = cpu.write_bus;
        word rupt_index = (rupt_address - 02000) / 4;
        cpu.interrupts[rupt_index] = false;
        cpu.iip = true;
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

    void rb14(Cpu& cpu) {
        cpu.write_bus |= BITMASK_14;
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

    void rlp(Cpu& cpu) {
        cpu.write_bus |= cpu.lp;
    }

    void rq(Cpu& cpu) {
        cpu.write_bus |= cpu.q;
    }

    void rp2(Cpu& cpu) {
        // TODO
    }

    void rs(Cpu& cpu) {
        cpu.write_bus |= cpu.s;
    }

    void rsb(Cpu& cpu) {
        cpu.write_bus |= BITMASK_16;
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
            case 4:
            case 5:
            case 6:
            case 7:
                cpu.write_bus |= cpu.in[cpu.s - 4];
                break;
            case 010:
            case 011:
            case 012:
            case 013:
            case 014:
                cpu.write_bus |= cpu.out[cpu.s - 010];
                break;
            case 015:
                cpu.write_bus |= (cpu.bank << 10);
                break;
        }
    }

    void rsct(Cpu& cpu) {
        for (word c = 0; c < 20; ++c) {
            if (cpu.counters[c] != COUNTER_STATUS::NONE) {
                cpu.write_bus |= c + 034;
                break;
            }
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
        cpu.write_bus |= 0177776;
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

    void rrpa(Cpu& cpu) {
        for (int i = 0; i < 6; ++i) {
            if (cpu.interrupts[i]) {
                word rupt_address = 02000 + (i * 4);
                cpu.write_bus |= rupt_address;
                break;
            }
        }
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
        } else  {
            cpu.br &= 0b10; // Reset LSB (BR 2) otherwise.
        }
    }

    void tov(Cpu& cpu) {
        word sign_bits = get_sign_bits(cpu.write_bus);
        if (sign_bits == 0b01 || sign_bits == 0b10) {
            cpu.br = sign_bits; // Set MSB (BR 1) on negative overflow, LSB (BR 2) on positive overflow.
        } else {
            cpu.br = 0;
        }
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
        } else {
            cpu.br &= 0b01; // Clear MSB (BR 1) if the sign bit is NOT set
        }
    }

    void tsgn2(Cpu& cpu) {
        if ((cpu.write_bus & BITMASK_15) > 0) {
            cpu.br |= 0b01; // Set LSB (BR 2) if sign bit is set
        } else {
            cpu.br &= 0b10; // Clear LSB (BR 2) if the sign bit is NOT set
        }
    }

    void wa(Cpu &cpu) {
        cpu.a = cpu.write_bus;
    }

    void walp(Cpu& cpu) {
        word bit_one = cpu.write_bus & 1;
        cpu.a = _shift_right(cpu.write_bus);
        cpu.lp &= BITMASK_14;
        cpu.lp |= (bit_one << 13);
    }

    void wb(Cpu &cpu) {
        cpu.b = cpu.write_bus;
    }

    void wg(Cpu& cpu) {
        word temp = cpu.write_bus & ~BITMASK_16;    // Mask out bit 16 (SG)
        temp |= (cpu.write_bus & BITMASK_15) << 1;  // Copy bit 15 into bit 16
        temp &= ~BITMASK_15;    // Mask out bit 15

        word s_correct = (cpu.s_temp > 0) ? cpu.s_temp : cpu.s;

        if (s_correct >= 020 && s_correct <= 023) {
            switch (s_correct) {
                case 020:   // Cycle Right
                {
                    temp = _cycle_right(cpu.write_bus);
                    break;
                }
                case 021:   // Shift Right
                {
                    temp = _shift_right(cpu.write_bus);
                    break;
                }
                case 022:   // Cycle Left
                {
                    temp = _cycle_left(cpu.write_bus);
                    break;
                }
                case 023:  // Shift Left
                {
                    temp = _shift_left(cpu.write_bus);
                    break;
                }
            }
        }

        cpu.g = temp;
    }

    void wlp(Cpu& cpu) {
        cpu.lp = _cycle_right_lp(cpu.write_bus);
    }

    void wovc(Cpu& cpu) {
        // If uncorrected sign and generated sign do not match, we have an overflow.
        word sign_bits = get_sign_bits(cpu.write_bus);
        if (sign_bits == 0b01 || sign_bits == 0b10) {
            cpu.counters[COUNTER_OVCTR] = COUNTER_STATUS::UP;
        }
    }

    void wovi(Cpu& cpu) {
        // If uncorrected sign and generated sign do not match, we have an overflow.
        word sign_bits = get_sign_bits(cpu.write_bus);
        if (sign_bits == 0b01 || sign_bits == 0b10) {
            cpu.inhibit_interrupts = true;
        }
    }

    void wovr(Cpu& cpu) {
        // TODO: This may be implemented incorrectly, as far as I know
        // the only counter that should overflow is TIME1 into TIME2.
        const word counter_location = cpu.s - 034;
        if (counter_location == COUNTER_TIME1) {
            // If uncorrected sign and generated sign do not match, we have an overflow.
            word sign_bits = get_sign_bits(cpu.write_bus);
            if (sign_bits == 0b01 || sign_bits == 0b10) {
                cpu.counters[COUNTER_TIME2] = COUNTER_STATUS::UP;   // Overflow into TIME2
            }
        }

        cpu.counters[counter_location] = COUNTER_STATUS::NONE;  // Reset the original counter request
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
                wa(cpu);
                break;
            case 1:
                wq(cpu);
                break;
            case 2:
                wz(cpu);
                break;
            case 3:
                wlp(cpu);
                break;
            case 4:
            case 5:
            case 6:
            case 7:
                cpu.in[cpu.s - 4] = cpu.write_bus;
                break;
            case 010:
            case 011:
            case 012:
            case 013:
            case 014:
                cpu.out[cpu.s - 010] = cpu.write_bus;
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