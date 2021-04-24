#ifndef AI_SAMPLING
#define AI_SAMPLING

#include <array>

#include "game/Move.hpp"

namespace ai
{
    rps::Move sample(const std::array<double, 3> &distribution);
}

#endif
