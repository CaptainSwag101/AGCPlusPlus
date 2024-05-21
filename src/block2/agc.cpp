#include "agc.hpp"

namespace agcplusplus::block2 {
Cpu Agc::cpu;
Memory Agc::memory;
Scaler Agc::scaler;
Timer Agc::timer;
Cdu Agc::cdu;
Imu Agc::imu;
InitArguments Agc::config;
std::ofstream Agc::log_stream;

Agc::Agc(const std::vector<word>& rope, const std::vector<word>& coredump, InitArguments init_args) {
    memory = Memory(MemoryInitState::BitsClear);
    config = init_args;
    cdu.add_channel("IMU_X", imu.theta_x);
    cdu.add_channel("IMU_Y", imu.theta_y);
    cdu.add_channel("IMU_Z", imu.theta_z);

    // Set up log output stream.
    log_stream.open("AGCPlusPlus.log");

    for (const word& w : rope) {
        static int fixed_addr = 0;
        memory.write_fixed_word(fixed_addr++, w);
    }

    int i = 0;
    for (const word& w : coredump) {
        switch (i) {
            case 0:
                cpu.a = w;
                break;
            case 1:
                cpu.l = w;
                break;
            case 2:
                cpu.q = w;
                break;
            case 3:
                cpu.eb = (w & BITMASK_8_10);
                cpu.update_bb();
                break;
            case 4:
                cpu.fb = (w & BITMASK_11_15);
                cpu.fb &= ~BITMASK_15;  // Mask out the old bit 15 which is invalid if taken from erasable memory
                cpu.fb |= ((w & BITMASK_16) >> 1);  // Move bit 16 into bit 15
                cpu.update_bb();
                break;
            case 5:
                cpu.z = w;
                break;
            case 6:
                cpu.bb = w;
                cpu.bb &= ~BITMASK_15;  // Mask out the old bit 15 which is invalid if taken from erasable memory
                cpu.bb |= ((w & BITMASK_16) >> 1);  // Move bit 16 into bit 15
                cpu.update_eb_fb();
                break;
            default:
                memory.write_erasable_word(i, w);
        }
        ++i;
    }
}

void Agc::run() {
    std::cout << "Computer started." << std::endl;
    cpu.start();
    timer.start();
}
}
