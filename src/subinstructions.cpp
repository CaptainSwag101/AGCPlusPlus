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
