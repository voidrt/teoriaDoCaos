#include <raylib.h>
#include "config.hpp"
#include "entities/verlet_object.hpp"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


Vector2 worldCentre = {kWindowWidth / 2, kWindowHeight / 2};

struct Simulation
{
    VerletObject pendulum;
    int pulses;
    float simulationSpeed;
    float startingAngle;
    float pendulumLength;
    float K;
    bool isPaused = true;

    Simulation() : pendulum(0.0f), pulses(0), simulationSpeed(1.0f), startingAngle(0.0f), pendulumLength(256.0f), K(0.9763f)
    {
    }

    void Reset(float angle)
    {
        pendulum.Reset(angle);
        isPaused = true;
        pulses = 0;
    }
};

float WrapAngle(float angle)
{
    float remainder = angle / kTwoPi;
    return angle - std::floor(remainder) * kTwoPi;
}

void InitGameWindow()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(kWindowWidth, kWindowHeight, "Rotor chutado");
    SetTargetFPS(60);
}


int main()
{
    InitGameWindow();
    float deltaPhysicsTime = 0.8f;
    Simulation simState;
    float hardcodedAngle = simState.startingAngle;

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_P)) simState.isPaused = !simState.isPaused;

        if (!simState.isPaused)
        {
            for (size_t i = 0; i < static_cast<int>(simState.simulationSpeed); ++i)
            {
                deltaPhysicsTime += kDeltaTime;

                if (deltaPhysicsTime >= 1.0f)
                {
                    const float pulse = simState.K * sin(simState.pendulum.GetAngle());
                    simState.pendulum.AddAcceleration(-(pulse / kDeltaTime));

                    simState.pulses += static_cast<int>(simState.simulationSpeed);

                    deltaPhysicsTime -= 1.0f;
                }

                simState.pendulum.Move(kDeltaTime);
            }
        }


        {
            const float currentAngle = simState.pendulum.GetAngle();
            const Vector2 pendulum = {worldCentre.x + simState.pendulumLength * sin(currentAngle), worldCentre.y + simState.pendulumLength * cos(currentAngle)};

            BeginDrawing();
            ClearBackground(BLACK);

            if (GuiButton((Rectangle){10, 45, 100, 40}, "Resetar"))
            {
                simState.Reset(0);
            }


            GuiSlider((Rectangle){ kWindowWidth- 250, 15, 200, 20 }, "Angulo inicial (rad)", TextFormat("%.2f", simState.startingAngle), &simState.startingAngle, 0,kTwoPi);
            GuiSlider((Rectangle){ kWindowWidth- 250, 35, 200, 20 }, "Constante K", TextFormat("%.2f", simState.K), &simState.K, 0, 100);
            GuiSlider((Rectangle){ kWindowWidth- 250, 55, 200, 20 }, "Comprimento do Pendulo", TextFormat("%.2f", simState.pendulumLength), &simState.pendulumLength, 0, 1000);
            GuiSlider((Rectangle){ kWindowWidth- 250, 75, 200, 20 }, "Velocidade da Simulacao", TextFormat("%.0f", simState.simulationSpeed), &simState.simulationSpeed, 0, 20);


            if (simState.startingAngle != hardcodedAngle)
            {
                hardcodedAngle = simState.startingAngle;
                simState.Reset(simState.startingAngle);
            }

            DrawFPS(10, 5);
            DrawText(TextFormat("Chutes: %d", simState.pulses), static_cast<int>(kWindowWidth / 2) - MeasureText("Chutes: %d", 1), 15, 20, RAYWHITE);

            DrawLineDashed(worldCentre, {worldCentre.x, kWindowHeight}, static_cast<int>(kWindowHeight / 120), 10, LIGHTGRAY);
            DrawCircleV(worldCentre, 20, RAYWHITE);

            DrawLineEx(worldCentre, pendulum, 2, DARKGRAY);
            DrawCircleV(worldCentre, 10, RED);
            DrawCircleV(pendulum, 15, RED);

            EndDrawing();
        }
    }
    CloseWindow();

    return 0;
}
