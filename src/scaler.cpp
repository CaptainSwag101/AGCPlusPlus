#include "scaler.hpp"

namespace agcplusplus {
Scaler::Scaler()
{
    std::cout << "Initializing scaler..." << std::endl;

    cur_state = 0;
    prev_state = 0;

    std::cout << "Initializing scaler done." << std::endl;
}

void Scaler::tick() {
    prev_state = cur_state;
    ++cur_state;
}
}
