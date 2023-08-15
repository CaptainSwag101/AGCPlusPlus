#include "subinstructions.hpp"
#include "control_pulses.hpp"
#include "agc.hpp"

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

    void dv0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                ra(cpu);
                wb(cpu);
                tsgn(cpu);
                break;
            case 3:
                rsc(cpu);
                wg(cpu);
                break;
            case 4:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rc(cpu);
                        wa(cpu);
                        break;
                }
                break;
            case 5:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        r1(cpu);
                        wlp(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        r2(cpu);
                        wlp(cpu);
                        break;
                }
                break;
            case 6:
                ra(cpu);
                wq(cpu);
                break;
            case 7:
                rg(cpu);
                wb(cpu);
                tsgn(cpu);
                wp(cpu);
                break;
            case 8:
                rb(cpu);
                wa(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rlp(cpu);
                        r2(cpu);
                        wb(cpu);
                        break;
                }
                break;
            case 10:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rb(cpu);
                        wlp(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        rc(cpu);
                        wa(cpu);
                        break;
                }
                break;
            case 11:
                r1(cpu);
                st1(cpu);
                wb(cpu);
                break;
        }
    }

    void dv1(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                r22(cpu);
                ws(cpu);
                break;
            case 2:
                rq(cpu);
                wg(cpu);
                break;
            case 3:
                rg(cpu);
                rsb(cpu);
                wq(cpu);
                wy(cpu);
                break;
            case 4:
                ra(cpu);
                wx(cpu);
                break;
            case 5:
                rlp(cpu);
                tsgn2(cpu);
                break;
            case 7:
                ru(cpu);
                tsgn(cpu);
                break;
            case 8:
                switch (cpu.br) {
                    case 0b10:
                    case 0b11:
                        ru(cpu);
                        wq(cpu);
                        break;
                }
                break;
            case 9:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rb(cpu);
                        rsb(cpu);
                        wg(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        rb(cpu);
                        wg(cpu);
                        break;
                }
                break;
            case 10:
                rg(cpu);
                wb(cpu);
                tsgn(cpu);
                break;
            case 11:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        st1(cpu);
                        break;
                    case 0b10:
                        rc(cpu);
                        wa(cpu);
                        st2(cpu);
                        break;
                    case 0b11:
                        rb(cpu);
                        wa(cpu);
                        st2(cpu);
                        break;
                }
                break;
        }
    }

    void minc(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rsct(cpu);
                ws(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                r1c(cpu);
                wy(cpu);
                break;
            case 6:
                rg(cpu);
                wx(cpu);
                wp(cpu);
                break;
            case 7:
                tp(cpu);
                break;
            case 8:
                wp(cpu);
                break;
            case 9:
                ru(cpu);
                clg(cpu);
                wp(cpu);
                break;
            case 10:
                ru(cpu);
                wg(cpu);
                wovr(cpu);
                break;
        }
    }

    void mp0(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                cpu.multiply_counter = 5;
                rb(cpu);
                ws(cpu);
                break;
            case 2:
                ra(cpu);
                wb(cpu);
                tsgn(cpu);
                break;
            case 3:
                rsc(cpu);
                wg(cpu);
                break;
            case 4:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rb(cpu);
                        wlp(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        rc(cpu);
                        wlp(cpu);
                        break;
                }
                break;
            case 5:
                rlp(cpu);
                wa(cpu);
                break;
            case 7:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        rg(cpu);
                        wy(cpu);
                        wp(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        rg(cpu);
                        wb(cpu);
                        wp(cpu);
                        break;
                }
                break;
            case 8:
                switch (cpu.br) {
                    case 0b00:
                    case 0b01:
                        gp(cpu);
                        tp(cpu);
                        break;
                    case 0b10:
                    case 0b11:
                        rc(cpu);
                        wy(cpu);
                        gp(cpu);
                        tp(cpu);
                        break;
                }
                break;
            case 9:
                ru(cpu);
                wb(cpu);
                tsgn2(cpu);
                break;
            case 10:
                switch (cpu.br) {
                    case 0b00:
                    case 0b10:
                        ra(cpu);
                        wlp(cpu);
                        tsgn(cpu);
                        break;
                    case 0b01:
                    case 0b11:
                        ra(cpu);
                        rb14(cpu);
                        wlp(cpu);
                        tsgn(cpu);
                        break;
                }
                break;
            case 11:
                switch (cpu.br) {
                    case 0b00:
                        st1(cpu);
                        walp(cpu);
                        break;
                    case 0b01:
                        r1(cpu);
                        r1c(cpu);
                        st1(cpu);
                        walp(cpu);
                        break;
                    case 0b10:
                        ru(cpu);
                        st1(cpu);
                        walp(cpu);
                        break;
                    case 0b11:
                        ru(cpu);
                        st1(cpu);
                        walp(cpu);
                        break;
                }
                break;
        }
    }

    void mp1(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                ra(cpu);
                wy(cpu);
                break;
            case 2:
                rlp(cpu);
                wa(cpu);
                tsgn(cpu);
                break;
            case 3:
                switch (cpu.br) {
                    case 0b10:
                    case 0b11:
                        rb(cpu);
                        wx(cpu);
                        break;
                }
                break;
            case 4:
                ra(cpu);
                wlp(cpu);
                break;
            case 5:
                rlp(cpu);
                tsgn(cpu);
                break;
            case 6:
                ru(cpu);
                walp(cpu);
                break;
            case 7:
                ra(cpu);
                wy(cpu);
                break;
            case 8:
                switch (cpu.br) {
                    case 0b10:
                    case 0b11:
                        rb(cpu);
                        wx(cpu);
                        break;
                }
                break;
            case 9:
                rlp(cpu);
                wa(cpu);
                break;
            case 10:
                ra(cpu);
                wlp(cpu);
                ctr(cpu);
                break;
            case 11:
                ru(cpu);
                st1(cpu);
                walp(cpu);
                break;
        }
    }

    void mp3(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rz(cpu);
                wy(cpu);
                ws(cpu);
                ci(cpu);
                break;
            case 2:
                rlp(cpu);
                tsgn(cpu);
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
                break;
            case 6:
                switch (cpu.br) {
                    case 0b10:
                    case 0b11:
                        rb(cpu);
                        wx(cpu);
                        break;
                }
                break;
            case 7:
                rg(cpu);
                rsc(cpu);
                wb(cpu);
                wp(cpu);
                break;
            case 8:
                rlp(cpu);
                wa(cpu);
                gp(cpu);
                tp(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
                break;
            case 10:
                ra(cpu);
                wlp(cpu);
                break;
            case 11:
                ru(cpu);
                walp(cpu);
                nisq(cpu);
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

    void pinc(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rsct(cpu);
                ws(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 4:
                r1(cpu);
                wy(cpu);
                break;
            case 6:
                rg(cpu);
                wx(cpu);
                wp(cpu);
                break;
            case 7:
                tp(cpu);
                break;
            case 8:
                wp(cpu);
                break;
            case 9:
                ru(cpu);
                clg(cpu);
                wp(cpu);
                break;
            case 10:
                ru(cpu);
                wg(cpu);
                wovr(cpu);
                break;
        }
    }

    void rsm(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                r24(cpu);
                ws(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 7:
                rg(cpu);
                wz(cpu);
                break;
            case 11:
                nisq(cpu);
                cpu.iip = false;
                Agc::scaler.interrupt_ended();
                break;
        }
    }

    void rupt1(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                r24(cpu);
                wy(cpu);
                ws(cpu);
                ci(cpu);
                break;
            case 3:
                wg(cpu);
                break;
            case 9:
                rz(cpu);
                wg(cpu);
                break;
            case 10:
                ru(cpu);
                wz(cpu);
                break;
            case 11:
                st1(cpu);
                st2(cpu);
                break;
        }
    }

    void rupt3(Cpu& cpu) {
        switch (cpu.timepulse) {
            case 1:
                rz(cpu);
                ws(cpu);
                break;
            case 2:
                rrpa(cpu);
                wz(cpu);
                break;
            case 3:
                rz(cpu);
                krpt(cpu);
                wg(cpu);
                break;
            case 9:
                rb(cpu);
                wsc(cpu);
                wg(cpu);
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

    void su0(Cpu& cpu) {
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
                rc(cpu);
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
                rp2(cpu);
                wsc(cpu);
                wg(cpu);
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