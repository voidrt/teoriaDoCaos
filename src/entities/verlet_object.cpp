#include "verlet_object.hpp"

#include "../config.hpp"

void VerletObject::AddAcceleration(const float newAcceleration)
{
    this->angularAcceleration += newAcceleration;
}

void VerletObject::Move(const float dt)
{
    const float angularVelocity = this->angle - this->previousAngle;
    this->previousAngle = this->angle;

    this->angle = this->previousAngle + angularVelocity + (this->angularAcceleration * dt * dt);

    this->angularAcceleration = 0.0f;
}
