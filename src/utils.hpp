#pragma once

#include <cmath>
#include "constants.hpp"


struct Utils{
    static float Mod2PI(float number)
    {
        const float remainder = number / kTwoPi;
        return number - std::floor(remainder) * kTwoPi;
    }
};