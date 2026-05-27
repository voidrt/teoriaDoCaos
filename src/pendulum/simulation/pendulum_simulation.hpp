#pragma once

#include "../object/verlet_object.hpp"
#include "../../constants.hpp"
#include "cmath"

struct PendulumSimulation
{
    private:
        float deltaPhysicsTime = 0.8f;

    public:
        VerletObject pendulum;
        int pulses;
        float simulationSpeed;
        float pendulumStartingAngle;
        float hardcodedAngle;
        float hardcodedK;
        float pendulumLength;
        float K;
        bool isPaused = true;

        explicit PendulumSimulation() : pendulum(0.0f),  pulses(0), simulationSpeed(1.0f), pendulumStartingAngle(0.0f), hardcodedAngle(0.0f),hardcodedK(0.971635f),
                                        pendulumLength(442.0f),
                                        K(0.971635f)
        {
        }

        bool Run();
        void Reset(float angle);
        void Restart();
};
