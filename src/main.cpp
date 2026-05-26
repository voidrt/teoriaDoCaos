#include <raylib.h>
#include "pendulum/simulation/pendulum_simulation.hpp"
#include "pendulum/ui/pendulum_ui.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

enum SimMode
{
    PENDULUM_SIMULATION,
    PHASE_MAP
};

void InitGameWindow()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(kWindowWidth, kWindowHeight, "Pendulo E Mapa Padrao");
    SetTargetFPS(60);
}

int main()
{
    InitGameWindow();
    PendulumSimulation simulation;
    auto simulationUI = PendulumUI(simulation);
    SimMode mode = PENDULUM_SIMULATION;

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_M)) mode = PHASE_MAP;
        if (IsKeyPressed(KEY_S)) mode = PENDULUM_SIMULATION;

        switch (mode)
        {
            case PENDULUM_SIMULATION:
                {
                    simulationUI.HandleInput();

                    BeginDrawing();
                    ClearBackground(BLACK);

                    simulationUI.RunSimulation();
                    simulationUI.DrawSliders();
                    simulationUI.DrawPendulum();


                    EndDrawing();
                }
                break;
            case PHASE_MAP:
                {
                    BeginDrawing();
                    ClearBackground(BLACK);
                    EndDrawing();
                }
                break;
        }
    }
    CloseWindow();

    return 0;
}
