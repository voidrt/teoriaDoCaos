#include <raylib.h>
#include "config.h"
#include "entities/verlet_object.hpp"

Camera2D camera = {0};
Vector2 worldCentre = {kWindowWidth / 2, kWindowHeight / 2};
auto ball = VerletObject({worldCentre.x * 1.5f, worldCentre.y});
Vector2 pendulumBody = {worldCentre.x - (kWindowWidth / 40), worldCentre.y};

void InitGameWindow()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(kWindowWidth, kWindowHeight, "Archery");
    SetTargetFPS(60);

    camera.target = worldCentre;
    camera.offset = worldCentre;

    camera.zoom = 1.0f;
}



void InitWorld()
{
}

int main()
{
    InitGameWindow();
    InitWorld();

    while (!WindowShouldClose())
    {
        ball.AddAcceleration({0, 100.0f});
        ball.Move(kDeltaTime);
        ball.ConstrainObject(worldCentre, Vector2Distance(worldCentre, {worldCentre.x * 1.5f, worldCentre.y}));

        BeginDrawing();
        BeginMode2D(camera);
        ClearBackground(BLACK);

        DrawRectangleV(pendulumBody, {kWindowWidth / 20, kWindowHeight / 2}, RAYWHITE);
        DrawCircleV(ball.GetPosition(), 15,RED);
        DrawLineEx(worldCentre, ball.GetPosition(), 5, RED);

        EndMode2D();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
