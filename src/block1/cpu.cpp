#include "cpu.hpp"
#include "agc.hpp"
#include "subinstructions.hpp"
#include "../common/util_functions.hpp"

namespace agcplusplus::block1 {
    void Cpu::go() {
        should_gojam = false;
        inhibit_interrupts = false;
        inkl = false;
        iip = false;
        z = 02030;
        current_subinstruction = subinstruction_data[0];
        fetch_new_subinstruction = false;
        extend = false;
        st = 2;
        bank = 1;

        // Clear all output registers except OUT4, per ND-1021041 page 4-231
        for (int o = 0; o < 4; ++o) {
            out[o] = 0;
        }
    }

    void Cpu::tick() {
        process_before_timepulse();
        process_timepulse();
        process_after_timepulse();
    }

    void Cpu::process_before_timepulse() {
        if (timepulse == 1) {
            // If we are performing GOJAM, override all else and do it
            if (should_gojam) {
                go();
            }

            // Service INKL
            if (inkl) {
                for (auto& counter : counters) {
                    if (counter == COUNTER_STATUS::UP) {
                        current_subinstruction = sub_pinc;
                        break;
                    } else if (counter == COUNTER_STATUS::DOWN) {
                        current_subinstruction = sub_minc;
                        break;
                    }
                }
            } else if (fetch_new_subinstruction) {
                fetch_new_subinstruction = false;
                extend_next = false;
                overflow = false;
            }
        }

        // If we aren't performing an INKL or a TC instruction at time 3,
        // indicate to the hardware alarm logic that all is well.
        if (timepulse == 3) {
            if (!inkl && current_subinstruction.name != "TC0") {
                Agc::scaler.tc_ended();
            }
        }

        // Data arrives from memory before T6, rather than T4 on Block II.
        if (timepulse == 6 && s >= 020) {
            // Inhibit memory access when performing MP1, DV1.
            if (extend && st == 1 && (sq == 011 || sq == 012)) {
                if (Agc::configuration.log_memory)
                    std::cout << "Inhibited memory read due to MP1 or DV1" << std::endl;
            } else {
                g = Agc::memory.read(s, bank);
            }
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
        // Normally, only the INDEX instruction is used for this purpose,
        // but the way it's implemented in the hardware, any memory
        // access to 016 or 017 will cause a RELINT or INHINT.
        if (timepulse == 5) {
            if (s == 016) {
                inhibit_interrupts = false;
            }
            if (s == 017) {
                inhibit_interrupts = true;
            }
        }

        // Do erasable memory writes after time 10.
        // This call happens regardless of whether we're actually attempting to
        // write to erasable or fixed memory, but the function internals
        // will take care of that for us and ignore writes to fixed memory.
        if (timepulse == 10) {
            // Inhibit memory access when performing MP1, DV1.
            if (extend && st == 1 && (sq == 011 || sq == 012)) {
                if (Agc::configuration.log_memory)
                    std::cout << "Inhibited memory write due to MP1 or DV1" << std::endl;
            } else {
                Agc::memory.write(s, g);
            }
        }

        // Fetch next subinstruction, or the next stage of the current one
        if (timepulse == 12) {
            // Push stage to its next pending value if we weren't just interrupted by a counter
            if (!inkl) {
                st = st_next;
                st_next = 0;
            }

            // Check for pending counter requests
            inkl = false;
            for (auto& counter : counters) {
                if (counter != COUNTER_STATUS::NONE && !Agc::configuration.ignore_counters) {
                    inkl = true;
                    break;
                }
            }

            if (fetch_new_subinstruction) {
                // Check for pending interrupts
                bool rupt_pending = false;
                for (bool interrupt : interrupts) {
                    if (interrupt) {
                        rupt_pending = true;
                        break;
                    }
                }

                // Check if the next instruction is EXTENDed (there is negative overflow in B)
                if (get_sign_bits(b) == 0b10) {
                    extend_next = true;
                }

                // If an interrupt is pending, and we aren't ignoring them for debugging,
                // and they aren't currently inhibited, and an interrupt isn't already happening,
                // and we aren't about to perform an extracode instruction next (implied by overflow pulse WOVI during the index),
                // and there isn't overflow, perform the interrupt instead of the instruction in B.
                if (rupt_pending && !Agc::configuration.ignore_interrupts && !inhibit_interrupts && !iip && !overflow) {
                    subinstruction rupt1 = sub_rupt1;
                    sq = rupt1.order_code;
                    extend = rupt1.extended;
                    st = rupt1.stage;
                } else {
                    sq = (b & BITMASK_13_16) >> 12;  // B13-16 to SQ1-4
                    extend = extend_next;
                }
            }

            // With our sequence, stage, and extend status updated, find the appropriate
            // subinstruction so we can execute it over the next MCT.
            bool found_good_subinstruction = false;
            for (const subinstruction& sub : subinstruction_data) {
                if (sub.extended == extend && sub.stage == st && (sub.order_code & sub.mask) == (sq & sub.mask)) {
                    current_subinstruction = sub;
                    found_good_subinstruction = true;
                    break;
                }
            }

            // Force STD2 on unimplemented subinstruction
            if (!found_good_subinstruction) {
                current_subinstruction = subinstruction_data[0];
                std::cout << "Replacing unknown subinstruction at " << std::oct << bank << "," << (z - 1) << std::dec << " with STD2" << std::endl;
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

        output << std::endl;

        output << current_subinstruction.name << " (T" << std::setw(2) << std::setfill('0') << (word)timepulse <<")" << std::endl;

        std::oct(output);

        output << " A = " << std::setw(6) << a;
        output << " Q = " << std::setw(6) << q;
        output << " Z = " << std::setw(6) << z;
        output << " LP = " << std::setw(6) << lp;
        output << " G = " << std::setw(6) << g;
        output << " B = " << std::setw(6) << b;
        output << '\n';

        output << " BNK = " << std::setw(2) << bank;
        output << " S = " << std::setw(4) << s;
        output << " SQ = " << std::setw(2) << sq;
        output << " ST = " << (word)st; // Cast from char to integer
        output << " BR = " << (br & 1) << ((br & 2) >> 1);
        output << " IIP = " << static_cast<word>(iip);
        output << " INKL = " << static_cast<word>(inkl);
        output << " OVR = " << static_cast<word>(overflow);
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

    void Cpu::queue_gojam() {
        should_gojam = true;
    }
}