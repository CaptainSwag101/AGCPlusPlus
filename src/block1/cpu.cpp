#include "cpu.hpp"
#include "agc.hpp"
#include "subinstructions.hpp"

namespace agcplusplus::block1 {
    void Cpu::go() {
        write_bus = 02030;
        inhibit_interrupts = false;
        inkl = false;
        b = 0;
        current_subinstruction = subinstruction_data[0];
        fetch_next_subinstruction = false;
        st = 2;
        bank = 1;
    }

    void Cpu::tick() {
        process_before_timepulse();
        process_timepulse();
        process_after_timepulse();
    }

    void Cpu::process_before_timepulse() {
        if (timepulse == 1)
        {
            if (st != 2) {
                fetch_next_subinstruction = false;
                extend_next = false;
            }
        }

        // Data arrives from memory at T6, rather than T4 on Block II.
        if (timepulse == 6) {
            s_temp = s;
            g = Agc::memory.read(s, bank);
        }
    }

    void Cpu::process_timepulse() {
        current_subinstruction.function(*this);
    }

    void Cpu::process_after_timepulse() {
        if ((Agc::configuration.log_mct && timepulse == 12) || Agc::configuration.log_timepulse) {
            print_state_info(std::cout);
        }

        // Reset write bus
        write_bus = 0;

        // Fetch next subinstruction if we should
        if (timepulse == 12) {
            st = st_next;
            st_next = 0;
            extend = extend_next;

            if (fetch_next_subinstruction) {
                sq = (b & BITMASK_13_16) >> 12;  // B13-16 to SQ1-4
                extend = extend_next;
            }

            bool found_good_subinstruction = false;
            for (const subinstruction& sub : subinstruction_data) {
                if (sub.extended == extend && sub.stage == st && (sub.order_code & sub.mask) == (sq & sub.mask)) {
                    current_subinstruction = sub;
                    found_good_subinstruction = true;
                    break;
                }
            }

            if (!found_good_subinstruction) {
                // Force STD2 on unimplemented subinstruction
                current_subinstruction = subinstruction_data[0];
                std::cout << "Replacing unknown subinstruction with STD2" << std::endl;
            }
        }

        // Increment/reset timepulse count
        if (timepulse < 12) {
            ++timepulse;
        } else {
            timepulse = 1;
        }
    }

    void Cpu::print_state_info(std::ostream& output) const {
        std::dec(output);

        output << current_subinstruction.name << " (T" << std::setw(2) << std::setfill('0') << (word)timepulse <<")" << std::endl;

        std::oct(output);

        output << " A = " << std::setw(6) << a;
        output << " Q = " << std::setw(6) << q;
        output << " Z = " << std::setw(6) << z;
        output << " LP = " << std::setw(6) << lp;
        output << " G = " << std::setw(6) << g;
        output << " B = " << std::setw(6) << b;
        output << '\n';

        output << " S = " << std::setw(6) << s;
        output << " SQ = " << std::setw(2) << sq;
        output << " ST = " << (word)st; // Cast from char to integer
        output << " BR = " << (br & 1) << ((br & 2) >> 1);
        output << " BNK = " << std::setw(2) << bank;
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

    void Cpu::update_adder() {
        // Basic addition step
        uint32_t temp = x + y;

        // Handle carries
        uint32_t carry = carry_in ? 1 : 0;    // Explicit carry
        if (!no_eac)
            carry |= ((temp >> 16) & 1);    // End-around carry if not inhibited
        temp += carry;

        u = (word)temp;
    }
}