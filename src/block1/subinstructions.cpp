#include "subinstructions.hpp"
#include "control_pulses.hpp"

namespace agcplusplus::block1 {
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
}