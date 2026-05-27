#include "pendulum_ui.hpp"

void PendulumUI::ClearMiniMap() const
{
    BeginTextureMode(this->standardMap);
    ClearBackground(BLACK);
    EndTextureMode();
}


void PendulumUI::HandleInput() const
{
    if (IsKeyPressed(KEY_SPACE)) this->pendulumSim.isPaused = !this->pendulumSim.isPaused;
    if (this->pendulumSim.pendulumStartingAngle != this->pendulumSim.hardcodedAngle)
    {
        this->pendulumSim.hardcodedAngle = this->pendulumSim.pendulumStartingAngle;
        this->pendulumSim.Reset(this->pendulumSim.pendulumStartingAngle);
    }
    if (this->pendulumSim.K != this->pendulumSim.hardcodedK)
    {
        this->pendulumSim.hardcodedK = this->pendulumSim.K;
        this->pendulumSim.Reset(this->pendulumSim.pendulumStartingAngle);
        this->ClearMiniMap();
    }
}

void PendulumUI::DrawSliders() const
{
    if (GuiButton((Rectangle){10, 45, 100, 40}, "Recomecar") || IsKeyPressed(KEY_R))
    {
        this->pendulumSim.Restart();
    }
    if (this->pendulumSim.isPaused)
    {
        GuiSlider((Rectangle){kWindowWidth - 450, 15, 300, 40}, "Angulo inicial (rad)", TextFormat("%.2f", this->pendulumSim.pendulumStartingAngle),
            &this->pendulumSim.pendulumStartingAngle, 0, kTwoPi);
        GuiSlider((Rectangle){kWindowWidth - 450, 75, 300, 40}, "Constante K", TextFormat("%.2f", this->pendulumSim.K), &this->pendulumSim.K, 0.1, 10);
        GuiSlider((Rectangle){kWindowWidth - 450, 135, 300, 40}, "Comprimento do Pendulo", TextFormat("%.2f", this->pendulumSim.pendulumLength),
            &this->pendulumSim.pendulumLength, 10, 1000);
        GuiSlider((Rectangle){kWindowWidth - 450, 195, 300, 40}, "Velocidade da Simulacao", TextFormat("%.0f", this->pendulumSim.simulationSpeed),
            &this->pendulumSim.simulationSpeed, 1, 100);
    }
}

void PendulumUI::DrawPendulum() const
{
    const Vector2 pendulum = {
        worldCentre.x + this->pendulumSim.pendulumLength * sinf(this->pendulumSim.pendulum.GetAngle()),
        worldCentre.y + this->pendulumSim.pendulumLength * cosf(this->pendulumSim.pendulum.GetAngle())
    };

    DrawFPS(10, 5);
    DrawText(TextFormat("Chutes: %d", this->pendulumSim.pulses), static_cast<int>(kWindowWidth / 2) - MeasureText("Chutes: %d", 1), 15, 20, RAYWHITE);

    DrawLineEx(worldCentre, {worldCentre.x, kWindowHeight}, 1, LIGHTGRAY);
    DrawCircleV(worldCentre, 40, RAYWHITE);

    DrawLineEx(worldCentre, pendulum, 5, LIGHTGRAY);
    DrawCircleV(worldCentre, 20, RED);
    DrawCircleV(pendulum, 25, RED);
}

void PendulumUI::DrawMiniMap(const bool pulseApplied) const
{

    DrawRectangleLines(kWindowWidth - kMiniMapWidth - 25.0f, 15.0f, kMiniMapWidth+10.0f, kMiniMapHeight+10.0f, LIGHTGRAY);
    DrawText("0", kWindowWidth - kMiniMapWidth - 35.0f, kMiniMapHeight + 25.0f, 12,RAYWHITE);
    DrawText("P", kWindowWidth - (kMiniMapWidth/2.0f)  - GuiGetTextWidth("P"), kMiniMapHeight + 25.0f, 12,RAYWHITE);
    DrawText("2pi", kWindowWidth - 25.0f - GuiGetTextWidth("2pi"), kMiniMapHeight + 25.0f, 12,RAYWHITE);
    DrawText("Theta", kWindowWidth - kMiniMapWidth - 35.0f - GuiGetTextWidth("Theta"), (kMiniMapHeight / 2) + 25.0f, 12,RAYWHITE);
    DrawText("2pi", kWindowWidth - kMiniMapWidth - 35.0f - GuiGetTextWidth("2pi"), 25.0f, 12,RAYWHITE);

    if (pulseApplied)
    {
        const float velocity = Utils::Mod2PI(this->pendulumSim.pendulum.GetVelocity(kDeltaTime));
        const float angle = Utils::Mod2PI(this->pendulumSim.pendulum.GetAngle());

        const float normalizedX = velocity / kTwoPi, normalizedY = angle / kTwoPi;
        const float mapPointX = normalizedX * kMiniMapWidth, mapPointY = (1.0f - normalizedY) * (kMiniMapHeight);

        BeginTextureMode(this->standardMap);
        DrawRectangle(mapPointX, mapPointY, 2, 2, RAYWHITE);
        EndTextureMode();
    }
    const Rectangle miniMap = {
        0.0f, 0.0f, static_cast<float>(this->standardMap.texture.width), static_cast<float>(-this->standardMap.texture.height)
    };

    DrawTextureRec(this->standardMap.texture, miniMap, {kWindowWidth - kMiniMapWidth - 20.0f, 20.0f}, RAYWHITE);
}

void PendulumUI::RunSimulation() const
{
    if (!this->pendulumSim.isPaused)
    {
        for (size_t i = 0; i < static_cast<int>(this->pendulumSim.simulationSpeed); ++i)
        {
            const bool kicked = this->pendulumSim.Run();
            this->DrawMiniMap(kicked);
        }
    }
}
