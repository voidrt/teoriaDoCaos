#pragma once

#include <cmath>
#include "constants.hpp"


struct Utils
{
    static float Mod2PI(const float number)
    {
        const float remainder = number / kTwoPi;
        return number - std::floor(remainder) * kTwoPi;
    }

    static void FullscreenHelper()
    {
        if (IsKeyPressed(KEY_F) && IsKeyDown(KEY_LEFT_ALT))
        {
            auto monitor = GetCurrentMonitor();

            if (IsWindowFullscreen())
            {
                SetWindowSize(kWindowWidth, kWindowHeight);
            }
            else
            {
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
            }
            ToggleFullscreen();
        }
    }
};
