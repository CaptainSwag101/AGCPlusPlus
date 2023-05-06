#include "subinstructions.hpp"
#include "control_pulses.hpp"

namespace agcplusplus::block1 {
    void ad0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                ra(cpu);
                wy(cpu);
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
                rb(cpu);
                wx(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 11:
                ru(cpu);
                wa(cpu);
                wovc(cpu);
                st2(cpu);
                wovi(cpu);
                break;
        }
    }

    void ccs0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                rz(cpu);
                wy(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 6:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                tsgn(cpu);
                wp(cpu);
                break;
            case 7:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rc(cpu);
                        tmz(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        rb(cpu);
                        tmz(cpu);
                        break;
                }
                break;
            case 8:
                switch (cpu.br) {
                    case 0b00:
                        gp(cpu);
                        tp(cpu);
                        break;
                    case 0b01:
                        r1(cpu);
                        wx(cpu);
                        gp(cpu);
                        tp(cpu);
                        break;
                    case 0b10:
                        r2(cpu);
                        wx(cpu);
                        gp(cpu);
                        tp(cpu);
                        break;
                    case 0b11:
                        r1(cpu);
                        r2(cpu);
                        wx(cpu);
                        gp(cpu);
                        tp(cpu);
                        break;
                }
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 10:
                switch (cpu.br) {
                    case 0b00:
                        rc(cpu);
                        wa(cpu);
                        break;
                    case 0b10:
                        rb(cpu);
                        wa(cpu);
                        break;
                    case 0b01:
                    case 0b11:
                        r1c(cpu);
                        wa(cpu);
                        break;
                }
                break;
            case 11:
                ru(cpu);
                st1(cpu);
                wz(cpu);
                break;
        }
    }

    void ccs1(Cpu& cpu) {
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
            case 5:
                ra(cpu);
                wy(cpu);
                ci(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                ru(cpu);
                wb(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 10:
                rc(cpu);
                wa(cpu);
                wovi(cpu);
                break;
            case 11:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                nisq(cpu);
                break;
        }
    }

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

    void msk0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                ra(cpu);
                wb(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                rc(cpu);
                wy(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                ru(cpu);
                rc(cpu);
                wa(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 10:
                ra(cpu);
                wb(cpu);
                break;
            case 11:
                rc(cpu);
                wa(cpu);
                st2(cpu);
                wovi(cpu);
                break;
        }
    }

    void ndx0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
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
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 10:
                trsm(cpu);
                break;
            case 11:
                st1(cpu);
                break;
        }
    }

    void ndx1(Cpu& cpu) {
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
            case 6:
                rb(cpu);
                wy(cpu);
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                rb(cpu);
                wx(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 11:
                ru(cpu);
                wb(cpu);
                wovi(cpu);
                nisq(cpu);
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
                rb(cpu);
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