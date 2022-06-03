#include "subinstructions.hpp"

namespace agcplusplus {
void ad0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rb(cpu);
        wy(cpu);
        a2x(cpu);
        break;
    case 11:
        ru(cpu);
        wa(cpu);
        break;
    }
}

void ads0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        rb(cpu);
        wy(cpu);
        a2x(cpu);
        break;
    case 6:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        tov(cpu);
        break;
    case 7:
        switch (cpu.br) {
        case 0b00:
        case 0b11:
            wa(cpu);
            break;
        case 0b01:
            rb1(cpu);
            wa(cpu);
            break;
        case 0b10:
            r1c(cpu);
            wa(cpu);
            break;
        }
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rc(cpu);
        tmz(cpu);
        break;
    case 11:
        ru(cpu);
        wa(cpu);
        break;
    }
}

void bzf0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        ra(cpu);
        wg(cpu);
        tsgn(cpu);
        tmz(cpu);
        break;
    case 2:
        tpzg(cpu);
        break;
    case 3:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        switch (cpu.br) {
        case 0b01:
        case 0b11:
            rb(cpu);
            wy12(cpu);
            ci(cpu);
            break;
        }
        break;
    case 6:
        switch (cpu.br) {
        case 0b01:
        case 0b11:
            ru(cpu);
            wz(cpu);
            break;
        }
        break;
    case 8:
        switch (cpu.br) {
        case 0b00:
        case 0b10:
            rz(cpu);
            ws(cpu);
            st2(cpu);
            break;
        case 0b01:
        case 0b11:
            rad(cpu);
            wb(cpu);
            ws(cpu);
            nisq(cpu);
            break;
        }
        break;
    }
}

void ca0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rb(cpu);
        wa(cpu);
        break;
    }
}

void ccs0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        rg(cpu);
        wb(cpu);
        tsgn(cpu);
        tmz(cpu);
        tpzg(cpu);
    case 7:
        switch (cpu.br) {
        case 0b00:
            rz(cpu);
            wy12(cpu);
            break;
        case 0b01:
            rz(cpu);
            wy12(cpu);
            ponex(cpu);
            break;
        case 0b10:
            rz(cpu);
            wy12(cpu);
            ptwox(cpu);
            break;
        case 0b11:
            rz(cpu);
            wy12(cpu);
            ponex(cpu);
            ptwox(cpu);
            break;
        }
        break;
    case 8:
        ru(cpu);
        wz(cpu);
        ws(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        switch (cpu.br) {
        case 0b00:
            rb(cpu);
            wy(cpu);
            monex(cpu);
            ci(cpu);
            st2(cpu);
            break;
        case 0b01:
        case 0b11:
            wy(cpu);
            st2(cpu);
            break;
        case 0b10:
            rc(cpu);
            wy(cpu);
            monex(cpu);
            ci(cpu);
            st2(cpu);
            break;
        }
        break;
    case 11:
        ru(cpu);
        wa(cpu);
        break;
    }
}

void cs0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rc(cpu);
        wa(cpu);
        break;
    }
}

void dca0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rb(cpu);
        wy12(cpu);
        monex(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        ru(cpu);
        ws(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rb(cpu);
        wl(cpu);
        st1(cpu);
        break;
    }
}

void dca1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rb(cpu);
        wa(cpu);
        break;
    }
}

void dcs0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rb(cpu);
        wy12(cpu);
        monex(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        ru(cpu);
        ws(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rc(cpu);
        wl(cpu);
        st1(cpu);
        break;
    }
}

void dcs1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        rc(cpu);
        wa(cpu);
        break;
    }
}

void dxch0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        wy12(cpu);
        monex(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        rl(cpu);
        wb(cpu);
        break;
    case 5:
        rg(cpu);
        wl(cpu);
        break;
    case 7:
        rb(cpu);
        wsc(cpu);
        wg(cpu);
        break;
    case 8:
        ru(cpu);
        ws(cpu);
        wb(cpu);
        break;
    case 10:
        st1(cpu);
        break;
    }
}

void dxch1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        ra(cpu);
        wb(cpu);
        break;
    case 5:
        rg(cpu);
        wa(cpu);
        break;
    case 7:
        rb(cpu);
        wsc(cpu);
        wg(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void goj1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 8:
        rstrt(cpu);
        ws(cpu);
        wb(cpu);
        break;
    }
}

void msk0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        ra(cpu);
        wb(cpu);
        break;
    case 4:
        rc(cpu);
        wa(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rc(cpu);
        ra(cpu);
        wy(cpu);
        break;
    case 10:
        ru(cpu);
        wb(cpu);
        break;
    case 11:
        rc(cpu);
        wa(cpu);
        break;
    }
}

void ndx0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        trsm(cpu);
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        break;
    case 10:
        st1(cpu);
        break;
    }
}

void ndx1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rz(cpu);
        wy12(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        nisq(cpu);
        break;
    case 3:
        rb(cpu);
        wz(cpu);
        break;
    case 4:
        ra(cpu);
        wb(cpu);
        break;
    case 5:
        rz(cpu);
        wa(cpu);
        break;
    case 6:
        ru(cpu);
        wz(cpu);
        break;
    case 7:
        rg(cpu);
        wy(cpu);
        a2x(cpu);
        break;
    case 8:
        ru(cpu);
        ws(cpu);
        break;
    case 9:
        rb(cpu);
        wa(cpu);
        break;
    case 10:
        ru(cpu);
        wb(cpu);
        break;
    }
}

void qxch0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        rq(cpu);
        wb(cpu);
        break;
    case 5:
        rg(cpu);
        wq(cpu);
        break;
    case 7:
        rb(cpu);
        wsc(cpu);
        wg(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void std2(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rz(cpu);
        wy12(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        nisq(cpu);
        break;
    case 6:
        ru(cpu);
        wz(cpu);
        break;
    case 8:
        rad(cpu);
        wb(cpu);
        ws(cpu);
        break;
    }
}

void tc0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rb(cpu);
        wy12(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        nisq(cpu);
        break;
    case 3:
        rz(cpu);
        wq(cpu);
        break;
    case 6:
        ru(cpu);
        wz(cpu);
        break;
    case 8:
        rad(cpu);
        wb(cpu);
        ws(cpu);
        break;
    }
}

void tcf0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rb(cpu);
        wy12(cpu);
        ci(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        nisq(cpu);
        break;
    case 6:
        ru(cpu);
        wz(cpu);
        break;
    case 8:
        rad(cpu);
        wb(cpu);
        ws(cpu);
        break;
    }
}

void ts0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        ra(cpu);
        wb(cpu);
        tov(cpu);
        break;
    case 4:
        switch (cpu.br) {
        case 0b00:
        case 0b11:
            rz(cpu);
            wy12(cpu);
            break;
        case 0b01:
        case 0b10:
            rz(cpu);
            wy12(cpu);
            ci(cpu);
            break;
        }
        break;
    case 5:
        switch (cpu.br) {
        case 0b01:
            rb1(cpu);
            wa(cpu);
            break;
        case 0b10:
            r1c(cpu);
            wa(cpu);
            break;
        }
        break;
    case 6:
        ru(cpu);
        wz(cpu);
        break;
    case 7:
        rb(cpu);
        wsc(cpu);
        wg(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void wand0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        ra(cpu);
        wb(cpu);
        break;
    case 3:
        rc(cpu);
        wy(cpu);
        break;
    case 4:
        rch(cpu);
        wb(cpu);
        break;
    case 5:
        rc(cpu);
        ru(cpu);
        wa(cpu);
        break;
    case 6:
        ra(cpu);
        wb(cpu);
        break;
    case 7:
        rc(cpu);
        wa(cpu);
        wch(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void xch0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        ra(cpu);
        wb(cpu);
        break;
    case 5:
        rg(cpu);
        wa(cpu);
        break;
    case 7:
        rb(cpu);
        wsc(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
    }
}
}
