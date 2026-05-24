#include "verlet_object.hpp"

#include "../config.hpp"

void VerletObject::AddAcceleration(const float newAcceleration)
{
    this->m_angularAcceleration += newAcceleration;
}

void VerletObject::Move(const float dt)
{
    const float angularVelocity = this->m_angle - this->m_previousAngle;
    this->m_previousAngle = this->m_angle;

    this->m_angle = this->m_previousAngle + angularVelocity + (this->m_angularAcceleration * dt * dt);

    this->m_angularAcceleration = 0.0f;
}

void VerletObject::Reset(float initialAngle)
{
    this->m_angle = initialAngle;
    this->m_previousAngle = initialAngle;

    this->m_angularAcceleration = {};
}
