#pragma once
#include "../simulation/pendulum_simulation.hpp"
#include "raylib.h"
#include "../../utils.hpp"
#include "raygui.h"
#include <cmath>

class PendulumUI
{
    private:
        PendulumSimulation& pendulumSim;
        Vector2 worldCentre = {kWindowWidth / 2, kWindowHeight / 2};
        RenderTexture2D standardMap;

    public:
        explicit PendulumUI(PendulumSimulation& simulation) : pendulumSim(simulation), standardMap(LoadRenderTexture(kWindowWidth, kWindowHeight))
        {
            BeginTextureMode(standardMap);
            ClearBackground(BLACK);
            EndTextureMode();
        }

        void HandleInput() const;
        void DrawPendulum() const;
        void DrawSliders() const;
        void DrawMiniMap(bool pulseApplied) const;
        void RunSimulation() const;
        void ClearMiniMap() const;
};
