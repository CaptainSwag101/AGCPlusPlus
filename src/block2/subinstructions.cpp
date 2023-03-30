#include "subinstructions.hpp"

namespace agcplusplus::block2 {
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
        rg(cpu);
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

void aug0(Cpu& cpu) {
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
        rg(cpu);
        wy(cpu);
        tsgn(cpu);
        tmz(cpu);
        tpzg(cpu);
        break;
    case 6:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            ponex(cpu);
            break;
        case 0b10:
        case 0b11:
            monex(cpu);
            break;
        }
        break;
    case 7:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        wovr(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
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

void bzmf0(Cpu& cpu) {
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
        case 0b10:
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
        case 0b10:
        case 0b11:
            ru(cpu);
            wz(cpu);
            break;
        }
        break;
    case 8:
        switch (cpu.br) {
        case 0b00:
            rz(cpu);
            ws(cpu);
            st2(cpu);
            break;
        case 0b01:
        case 0b10:
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
        break;
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
        break;
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

void das0(Cpu& cpu) {
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
        ra(cpu);
        wb(cpu);
        break;
    case 4:
        rl(cpu);
        wa(cpu);
        break;
    case 5:
        ru(cpu);
        wl(cpu);
        break;
    case 6:
        rg(cpu);
        wy(cpu);
        a2x(cpu);
        break;
    case 7:
        rb(cpu);
        wa(cpu);
        break;
    case 8:
        rl(cpu);
        wb(cpu);
        break;
    case 9:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        tov(cpu);
        break;
    case 10:
        switch (cpu.br) {
        case 0b00:
        case 0b11:
            ra(cpu);
            wy(cpu);
            st1(cpu);
            break;
        case 0b01:
            ra(cpu);
            wy(cpu);
            st1(cpu);
            ponex(cpu);
            break;
        case 0b10:
            ra(cpu);
            wy(cpu);
            st1(cpu);
            monex(cpu);
            break;
        }
        break;
    }
}

void das1(Cpu& cpu) {
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
        ru(cpu);
        wa(cpu);
        break;
    case 5:
        rg(cpu);
        wy(cpu);
        a2x(cpu);
        break;
    case 6:
        ru(cpu);
        wg(cpu);
        wsc(cpu);
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
    case 10:
        switch (cpu.br) {
        case 0b00:
        case 0b10:
            wl(cpu);
            break;
        }
        break;
    case 11:
        switch (cpu.br) {
        case 0b01:
        case 0b11:
            ru(cpu);
            wa(cpu);
            break;
        }
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

void dim0(Cpu& cpu) {
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
        rg(cpu);
        wy(cpu);
        tsgn(cpu);
        tmz(cpu);
        tpzg(cpu);
        break;
    case 6:
        switch (cpu.br) {
        case 0b00:
            monex(cpu);
            break;
        case 0b10:
            ponex(cpu);
            break;
        }
        break;
    case 7:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        wovr(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void dinc(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rsct(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        rg(cpu);
        wy(cpu);
        tsgn(cpu);
        tmz(cpu);
        tpzg(cpu);
        break;
    case 6:
        switch (cpu.br) {
        case 0b00:
            monex(cpu);
            pout(cpu);
            break;
        case 0b10:
            ponex(cpu);
            mout(cpu);
            break;
        case 0b01:
        case 0b11:
            zout(cpu);
            break;
        }
        break;
    case 7:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        wovr(cpu);
        break;
    case 8:
        rb(cpu);
        ws(cpu);
        break;
    }
}

void dv0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        _1xp10(cpu);
        ra(cpu);
        wb(cpu);
        tsgn(cpu);
        tmz(cpu);
        break;
    case 2:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            rc(cpu);
            wa(cpu);
            tmz(cpu);
            dvst(cpu);
            break;
        case 0b10:
        case 0b11:
            dvst(cpu);
            break;
        }
        break;
    case 3:
        ru(cpu);
        wb(cpu);
        stage(cpu);
        break;
    }
}

void dv1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 4:
        switch (cpu.br) {
        case 0b00:
        case 0b10:
            rl(cpu);
            wb(cpu);
            break;
        case 0b01:
        case 0b11:
            rl(cpu);
            wb(cpu);
            tsgn(cpu);
            break;
        }
        break;
    case 5:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            rb(cpu);
            wy(cpu);
            b15x(cpu);
            break;
        case 0b10:
        case 0b11:
            rc(cpu);
            wy(cpu);
            b15x(cpu);
            z16(cpu);
            break;
        }
        break;
    case 6:
        ru(cpu);
        wl(cpu);
        tov(cpu);
        break;
    case 7:
        rg(cpu);
        rsc(cpu);
        wb(cpu);
        tsgn(cpu);
        break;
    case 8:
        switch (cpu.br) {
        case 0b00:
        case 0b10:
            ra(cpu);
            wy(cpu);
            ponex(cpu);
            _8xp5(cpu);
            break;
        case 0b01:
        case 0b11:
            ra(cpu);
            wy(cpu);
            _8xp5(cpu);
            break;
        }
        break;
    case 9:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            rb(cpu);
            wa(cpu);
            break;
        case 0b10:
        case 0b11:
            rc(cpu);
            wa(cpu);
            z15(cpu);
            break;
        }
        break;
    case 10:
        ru(cpu);
        wb(cpu);
        break;
    case 11:
        rl(cpu);
        wyd(cpu);
        break;
    case 12:
        ru(cpu);
        wl(cpu);
        break;
    case 1:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 2:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        dvst(cpu);
        break;
    case 3:
        ru(cpu);
        wb(cpu);
        stage(cpu);
        break;
    }
}

void dv3(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 4:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 5:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 6:
        ru(cpu);
        wb(cpu);
        break;
    case 7:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 8:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 9:
        ru(cpu);
        wb(cpu);
        break;
    case 10:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 11:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 12:
        ru(cpu);
        wb(cpu);
        break;
    case 1:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 2:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        dvst(cpu);
        break;
    case 3:
        ru(cpu);
        wb(cpu);
        stage(cpu);
        break;
    }
}

void dv7(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 4:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 5:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 6:
        ru(cpu);
        wb(cpu);
        break;
    case 7:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 8:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 9:
        ru(cpu);
        wb(cpu);
        break;
    case 10:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 11:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 12:
        ru(cpu);
        wb(cpu);
        break;
    case 1:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 2:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        dvst(cpu);
        break;
    case 3:
        ru(cpu);
        wb(cpu);
        stage(cpu);
        break;
    }
}

void dv6(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 4:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 5:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 6:
        ru(cpu);
        wb(cpu);
        break;
    case 7:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 8:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 9:
        ru(cpu);
        wb(cpu);
        break;
    case 10:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 11:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        break;
    case 12:
        ru(cpu);
        wb(cpu);
        break;
    case 1:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 2:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wl(cpu);
        dvst(cpu);
        break;
    case 3:
        ru(cpu);
        wb(cpu);
        stage(cpu);
        break;
    }
}

void dv4(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 4:
        l2gd(cpu);
        rb(cpu);
        pifl(cpu);
        wyd(cpu);
        a2x(cpu);
        break;
    case 5:
        rg(cpu);
        tsgu(cpu);
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            clxc(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1f(cpu);
            break;
        }
        wb(cpu);
        wa(cpu);
        break;
    case 6:
        rz(cpu);
        tov(cpu);
        break;
    case 7:
        switch (cpu.br) {
        case 0b01:
        case 0b10:
        case 0b11:
            rc(cpu);
            wa(cpu);
            break;
        }
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        tsgn(cpu);
        rststg(cpu);
        break;
    case 9:
        ru(cpu);
        wb(cpu);
        wl(cpu);
        break;
    case 10:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            rc(cpu);
            wl(cpu);
            break;
        }
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

void lxch0(Cpu& cpu) {
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
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void incr0(Cpu& cpu) {
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
        rg(cpu);
        wy(cpu);
        tsgn(cpu);
        tmz(cpu);
        tpzg(cpu);
        break;
    case 6:
        ponex(cpu);
        break;
    case 7:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        wovr(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void mp0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        ra(cpu);
        wb(cpu);
        tsgn(cpu);
        break;
    case 4:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            rb(cpu);
            wl(cpu);
            break;
        case 0b10:
        case 0b11:
            rc(cpu);
            wl(cpu);
            break;
        }
        break;
    case 7:
        rg(cpu);
        wb(cpu);
        tsgn2(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        break;
    case 9:
        switch (cpu.br) {
        case 0b00:
            rb(cpu);
            wy(cpu);
            break;
        case 0b01:
            rb(cpu);
            wy(cpu);
            ci(cpu);
            break;
        case 0b10:
            rc(cpu);
            wy(cpu);
            ci(cpu);
            break;
        case 0b11:
            rc(cpu);
            wy(cpu);
            break;
        }
        break;
    case 10:
        ru(cpu);
        wb(cpu);
        tsgn(cpu);
        st1(cpu);
        neacon(cpu);
        break;
    case 11:
        switch (cpu.br) {
        case 0b00:
        case 0b01:
            wa(cpu);
            break;
        case 0b10:
        case 0b11:
            rb1(cpu);
            r1c(cpu);
            wa(cpu);
            l16(cpu);
            break;
        }
        break;
    }
}

void mp1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        zip(cpu);
        break;
    case 2:
        zap(cpu);
        break;
    case 3:
        zip(cpu);
        break;
    case 4:
        zap(cpu);
        break;
    case 5:
        zip(cpu);
        break;
    case 6:
        zap(cpu);
        break;
    case 7:
        zip(cpu);
        break;
    case 8:
        zap(cpu);
        break;
    case 9:
        zip(cpu);
        break;
    case 10:
        zap(cpu);
        st1(cpu);
        st2(cpu);
        break;
    case 11:
        zip(cpu);
        break;
    }
}

void mp3(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        zap(cpu);
        break;
    case 2:
        zip(cpu);
        nisq(cpu);
        break;
    case 3:
        zap(cpu);
        break;
    case 4:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        rz(cpu);
        wy12(cpu);
        ci(cpu);
        break;
    case 6:
        ru(cpu);
        wz(cpu);
        tl15(cpu);
        // NEACOF should happen here but a hardware fix extends it to the end of MP3
        break;
    case 7:
        switch (cpu.br) {
        case 0b10:
        case 0b11:
            rb(cpu);
            wy(cpu);
            a2x(cpu);
            break;
        }
        break;
    case 8:
        rad(cpu);
        wb(cpu);
        ws(cpu);
        break;
    case 9:
        ra(cpu);
        break;
    case 10:
        rl(cpu);
        break;
    case 11:
        switch (cpu.br) {
        case 0b10:
        case 0b11:
            ru(cpu);
            wa(cpu);
            break;
        }
        break;
    case 12:
        neacof(cpu);    // Extend NOEAC until it's released by hardware
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

void msu0(Cpu& cpu) {
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
        rg(cpu);
        wb(cpu);
        break;
    case 6:
        rc(cpu);
        wy(cpu);
        ci(cpu);
        a2x(cpu);
        break;
    case 7:
        rus(cpu);
        wa(cpu);
        tsgn(cpu);
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
        switch (cpu.br) {
        case 0b10:
        case 0b11:
            ra(cpu);
            wy(cpu);
            monex(cpu);
            break;
        }
        break;
    case 11:
        rus(cpu);
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

void ndxx0(Cpu& cpu) {
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

void ndxx1(Cpu& cpu) {
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
        ext(cpu);
        break;
    }
}

void pinc(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rsct(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 5:
        rg(cpu);
        wy(cpu);
        tsgn(cpu);
        tmz(cpu);
        tpzg(cpu);
        break;
    case 6:
        ponex(cpu);
        break;
    case 7:
        ru(cpu);
        wsc(cpu);
        wg(cpu);
        wovr(cpu);
        break;
    case 8:
        rb(cpu);
        ws(cpu);
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

void rand0(Cpu& cpu) {
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
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void read0(Cpu& cpu) {
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
        wy(cpu);
        break;
    case 4:
        rch(cpu);
        wb(cpu);
        break;
    case 5:
        rb(cpu);
        wa(cpu);
        break;
    case 6:
        ra(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void ror0(Cpu& cpu) {
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
        rb(cpu);
        wy(cpu);
        break;
    case 4:
        rch(cpu);
        wb(cpu);
        break;
    case 5:
        rb(cpu);
        ru(cpu);
        wa(cpu);
        break;
    case 6:
        ra(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void rsm3(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        r15(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        nisq(cpu);
        break;
    case 5:
        rg(cpu);
        wz(cpu);
        break;
    case 6:
        rb(cpu);
        wg(cpu);
        break;
    case 8:
        rad(cpu);
        wb(cpu);
        ws(cpu);
        cpu.iip = false;
        break;
    }
}

void rxor0(Cpu& cpu) {
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
        rch(cpu);
        wy(cpu);
        break;
    case 4:
        rch(cpu);
        wb(cpu);
        break;
    case 5:
        ra(cpu);
        rc(cpu);
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
        rc(cpu);
        wg(cpu);
        break;
    case 10:
        ru(cpu);
        wb(cpu);
        break;
    case 11:
        rc(cpu);
        rg(cpu);
        wa(cpu);
        break;
    }
}

void rupt0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        r15(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 9:
        rz(cpu);
        wg(cpu);
        break;
    case 10:
        st1(cpu);
        break;
    }
}

void rupt1(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        r15(cpu);
        rb2(cpu);
        ws(cpu);
        break;
    case 2:
        rsc(cpu);
        wg(cpu);
        break;
    case 3:
        rrpa(cpu);
        wz(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    case 9:
        rb(cpu);
        wg(cpu);
        krpt(cpu);
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

void su0(Cpu& cpu) {
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
        wy(cpu);
        a2x(cpu);
        break;
    case 11:
        ru(cpu);
        wa(cpu);
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

void wor0(Cpu& cpu) {
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
        rb(cpu);
        wy(cpu);
        break;
    case 4:
        rch(cpu);
        wb(cpu);
        break;
    case 5:
        rb(cpu);
        ru(cpu);
        wa(cpu);
        wch(cpu);
        break;
    case 6:
        ra(cpu);
        wb(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}

void write0(Cpu& cpu) {
    switch (cpu.current_timepulse) {
    case 1:
        rl10bb(cpu);
        ws(cpu);
        break;
    case 2:
        ra(cpu);
        wb(cpu);
        wg(cpu);
        break;
    case 3:
        wy(cpu);
        break;
    case 4:
        rch(cpu);
        wb(cpu);
        break;
    case 5:
        ra(cpu);
        wch(cpu);
        break;
    case 6:
        ra(cpu);
        wb(cpu);
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
        wg(cpu);
        break;
    case 8:
        rz(cpu);
        ws(cpu);
        st2(cpu);
        break;
    }
}
}
