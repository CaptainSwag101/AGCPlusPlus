#include "agc.hpp"

namespace agcplusplus {
    Agc::Agc() {
        std::cout << "Initializing computer state..." << std::endl;

        std::cout << "Initializing computer state done." << std::endl;
    }

    void Agc::run() {
        int64_t totalTicks = 0;
        for (int t = 1; t <= 12; ++t)
        {
            ++totalTicks;
        }
    }
}
