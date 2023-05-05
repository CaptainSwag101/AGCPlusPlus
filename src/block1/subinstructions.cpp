#include "subinstructions.hpp"
#include "control_pulses.hpp"

namespace agcplusplus::block1 {
    void cs0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 10:
                rc(cpu);
                wa(cpu);
                wovi(cpu);
                break;
            case 11:
                st2(cpu);
                break;
        }
    }

    void std2(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rz(cpu);
                wy(cpu);
                ws(cpu);
                ci(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                ru(cpu);
                wz(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 11:
                nisq(cpu);
                break;
        }
    }

    void tc0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                wy(cpu);
                ws(cpu);
                ci(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                ra(cpu);
                wovi(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                rz(cpu);
                wq(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                wb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 10:
                ru(cpu);
                wz(cpu);
                break;
            case 11:
                nisq(cpu);
                break;
        }
    }

    void ts0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                ra(cpu);
                wb(cpu);
                tov(cpu);
                wp(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                switch (cpu.br) {
                    case 0b01:
                    case 0b10:
                        rz(cpu);
                        wy(cpu);
                        ci(cpu);
                        break;
                }
                break;
            case 5:
                switch (cpu.br) {
                    case 0b01:
                        r1(cpu);
                        wa(cpu);
                        break;
                    case 0b10:
                        r1c(cpu);
                        wa(cpu);
                        break;
                }
                break;
            case 7:
                switch (cpu.br) {
                    case 0b01:
                    case 0b10:
                        ru(cpu);
                        wz(cpu);
                        break;
                }
                break;
            case 8:
                gp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 10:
                ra(cpu);
                wovi(cpu);
                break;
            case 11:
                st2(cpu);
                break;
        }
    }

    void xch0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                ra(cpu);
                wp(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                wp2(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                ra(cpu);
                wsc(cpu);
                rg(cpu);
                rp2(cpu);
                break;
            case 10:
                rb(cpu);
                wa(cpu);
                wovi(cpu);
                break;
            case 11:
                st2(cpu);
                break;
        }
    }
}