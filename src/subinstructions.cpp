#include "subinstructions.hpp"

namespace agcplusplus {
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
}
