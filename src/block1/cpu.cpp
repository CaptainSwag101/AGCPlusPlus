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
        fetch_new_subinstruction = false;
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
            // Service INKL
            if (inkl) {
                // Remember what we wanted to do, so we can come back to it later
                pending_subinstruction = current_subinstruction;

                for (auto& counter : counters) {
                    if (counter == COUNTER_STATUS::UP) {
                        current_subinstruction = sub_pinc;
                        break;
                    } else if (counter == COUNTER_STATUS::DOWN) {
                        current_subinstruction = sub_minc;
                        break;
                    }
                }
            }

            if (st != 2) {
                fetch_new_subinstruction = false;
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

        // If address 016 or 017 is present in S at time 5,
        // release or inhibit interrupts, respectively.
        if (timepulse == 5) {
            if (s == 016) {
                inhibit_interrupts = false;
            }
            if (s == 017) {
                inhibit_interrupts = true;
            }
            if (b == 0147777) { // EXTEND
                extend_next = true;
            }
        }

        // Do erasable memory writes after time 10
        if (timepulse == 10) {
            Agc::memory.write(s_temp, g);
        }

        // Fetch next subinstruction, or the next stage of the current one
        if (timepulse == 12) {
            // Push stage to its next pending value
            st = st_next;
            st_next = 0;
            extend = extend_next;

            if (fetch_new_subinstruction) {
                // Check for pending counter requests
                bool prev_inkl = inkl;
                inkl = false;
                for (auto & counter : counters) {
                    if (counter != COUNTER_STATUS::NONE && !pseudo && !Agc::configuration.ignore_counters) {
                        inkl = true;
                        break;
                    }
                }


                // If no counters need servicing, and we have a pending subinstruction, get back to it.
                if (!inkl && prev_inkl) {
                    current_subinstruction = pending_subinstruction;
                    //sq = current_subinstruction.order_code;
                    //extend_next = current_subinstruction.extended;
                    //st = current_subinstruction.stage;
                }


                // Check for pending interrupts
                bool rupt_pending = false;
                for (bool interrupt : interrupts) {
                    if (interrupt) {
                        rupt_pending = true;
                        break;
                    }
                }


                uint8_t a_signs = (a & BITMASK_15_16) >> 14;
                bool a_overflow = (a_signs == 0b01 || a_signs == 0b10);
                if (rupt_pending && !Agc::configuration.ignore_interrupts && !inhibit_interrupts && !iip && !extend_next && !pseudo && !a_overflow) {
                    subinstruction rupt1 = sub_rupt1;
                    sq = rupt1.order_code;
                    extend = rupt1.extended;
                    st = rupt1.stage;
                } else {
                    sq = (b & BITMASK_13_16) >> 12;  // B13-16 to SQ1-4
                    //extend = extend_next;
                }
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
                std::cout << "Replacing unknown subinstruction at " << std::oct << bank << "," << z << std::dec << " with STD2" << std::endl;
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
        output << std::endl << std::endl;

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