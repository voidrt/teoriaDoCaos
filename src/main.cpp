#include <raylib.h>
#include "config.hpp"
#include "entities/verlet_object.hpp"

Camera2D camera = {0};
Vector2 worldCentre = {kWindowWidth / 2, kWindowHeight / 2};
auto ball = VerletObject(kInitialAngle);
bool isPaused = true;

float wrapAngle(float angle)
{
    float rem = angle / kTwoPi;

    return angle - std::floor(rem) * kTwoPi;
}

void InitGameWindow()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(kWindowWidth, kWindowHeight, "Rotor chutado");
    SetTargetFPS(60);

    camera.target = worldCentre;
    camera.offset = worldCentre;

    camera.zoom = 1.0f;
}


int main()
{
    InitGameWindow();
    int pulses = 0;
    float deltaPhysicsTime = 1.0f;
    float wrappedAngle = wrapAngle(ball.GetAngle());

    while (!WindowShouldClose())
    {
        auto pauseText = "Simulacao Pausada";

        if (IsKeyPressed(KEY_P)) isPaused = !isPaused;

        if (!isPaused)
        {
            pauseText = "Simulacao Rolando";

            for (size_t i = 0; i < kSimulationSpeed; ++i)
            {
                deltaPhysicsTime += kDeltaTime;

                if (deltaPhysicsTime >= 1.0f)
                {
                    const float pulse = K * sin(ball.GetAngle());
                    ball.AddAcceleration(-(pulse / kDeltaTime));

                    pulses += kSimulationSpeed;

                    deltaPhysicsTime -= 1.0f;
                }

                ball.Move(kDeltaTime);
                wrappedAngle = wrapAngle(ball.GetAngle());
            }
        }


        {
            const Vector2 pendulum = {worldCentre.x + kPendulumLength * sin(wrappedAngle), worldCentre.y + kPendulumLength * cos(wrappedAngle)};

            BeginDrawing();
            ClearBackground(BLACK);

            DrawFPS(10,5);
            DrawText(TextFormat(pauseText), 10, 40, 20, RAYWHITE);
            DrawText(TextFormat("Chutes: %d", pulses), static_cast<int>(kWindowWidth / 2) - MeasureText("Chutes: %d", 1), 5, 20, RAYWHITE);
            DrawText(TextFormat("Angulo (°): %.2f", (wrappedAngle * 180.0f) / M_PI),
                static_cast<int>(kWindowWidth / 2) - MeasureText("Angulo (°: %d", 1), 45, 20, RAYWHITE);

            BeginMode2D(camera);

            DrawTriangle({worldCentre.x, worldCentre.y - 20}, {worldCentre.x - kWindowWidth / 6, kWindowHeight},
                {worldCentre.x + kWindowWidth / 6, kWindowHeight}, LIGHTGRAY);
            DrawTriangle({worldCentre.x, worldCentre.y + 20}, {(worldCentre.x - kWindowWidth / 6) + 20, kWindowHeight},
                {(worldCentre.x + kWindowWidth / 6) - 20, kWindowHeight}, BLACK);
            DrawLineDashed(worldCentre, {worldCentre.x, kWindowHeight}, kWindowHeight/120,10, LIGHTGRAY);


            DrawCircleV(worldCentre, 20, RAYWHITE);


            DrawLineEx(worldCentre, pendulum, 2, DARKGRAY);
            DrawCircleV(worldCentre, 10, RED);
            DrawCircleV(pendulum, 15, RED);

            EndMode2D();
            EndDrawing();
        }
    }
    CloseWindow();

    return 0;
}
