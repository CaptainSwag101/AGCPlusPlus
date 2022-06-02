#include "subinstructions.hpp"

namespace agcplusplus {
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
}
