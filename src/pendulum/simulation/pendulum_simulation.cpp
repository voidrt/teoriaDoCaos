#include "pendulum_simulation.hpp"

void PendulumSimulation::Reset(const float angle)
{
    pendulum.Reset(angle);
    isPaused = true;
    pulses = 0;
}

void PendulumSimulation::Restart()
{
    this->Reset(0.0f);
    this->pulses = 0;
    this->simulationSpeed = 1.0f;
    this->pendulumStartingAngle = 0.0f;
    this->hardcodedAngle = 0.0f;
    this->pendulumLength = 256.0f;
    this->K = 0.971635f;
}

bool PendulumSimulation::Run()
{
    bool pulseApplied = false;

    deltaPhysicsTime += kDeltaTime;
    if (deltaPhysicsTime >= 1.0f)
    {
        const float pulse = (this->K * -sinf(this->pendulum.GetAngle())) / kDeltaTime;

        this->pendulum.AddAcceleration(pulse);
        ++this->pulses;
        pulseApplied = true;

        deltaPhysicsTime -= 1.0f;
    }

    this->pendulum.Move(kDeltaTime);

    return pulseApplied;
}
