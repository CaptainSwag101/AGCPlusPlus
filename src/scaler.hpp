#include "globaldefs.hpp"

#pragma once

namespace agcplusplus {
class Scaler
{
public:
    Scaler();
    void tick();

private:
    uint64_t cur_state;
    uint64_t prev_state;
};
}
