#include "block1defs.hpp"
#include "cpu.hpp"

#pragma once

namespace agcplusplus::block1 {
    word _shift_right(word input);
    word _cycle_right(word input);
    word _shift_left(word input);
    word _cycle_left(word input);
    void ci(Cpu& cpu);
    void clg(Cpu& cpu);
    void ctr(Cpu& cpu);
    void gp(Cpu& cpu);
    void krpt(Cpu& cpu);
    void nisq(Cpu& cpu);
    void ra(Cpu& cpu);
    void rb(Cpu& cpu);
    void rb14(Cpu& cpu);
    void rc(Cpu& cpu);
    void rg(Cpu& cpu);
    void rlp(Cpu& cpu);
    void rq(Cpu& cpu);
    void rp2(Cpu& cpu);
    void rs(Cpu& cpu);
    void rsb(Cpu& cpu);
    void rsc(Cpu& cpu);
    void rsct(Cpu& cpu);
    void ru(Cpu& cpu);
    void rz(Cpu& cpu);
    void r1(Cpu& cpu);
    void r1c(Cpu& cpu);
    void r2(Cpu& cpu);
    void r22(Cpu& cpu);
    void r24(Cpu& cpu);
    void rrpa(Cpu& cpu);
    void st1(Cpu& cpu);
    void st2(Cpu& cpu);
    void tmz(Cpu& cpu);
    void tov(Cpu& cpu);
    void tp(Cpu& cpu);
    void trsm(Cpu& cpu);
    void tsgn(Cpu& cpu);
    void tsgn2(Cpu& cpu);
    void wa(Cpu& cpu);
    void walp(Cpu& cpu);
    void wb(Cpu& cpu);
    void wg(Cpu& cpu);
    void wlp(Cpu& cpu);
    void wovc(Cpu& cpu);
    void wovi(Cpu& cpu);
    void wovr(Cpu& cpu);
    void wp(Cpu& cpu);
    void wp2(Cpu& cpu);
    void wq(Cpu& cpu);
    void ws(Cpu& cpu);
    void wsc(Cpu& cpu);
    void wx(Cpu& cpu);
    void wy(Cpu& cpu);
    void wz(Cpu& cpu);
}
