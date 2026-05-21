#include "verlet_object.hpp"

void VerletObject::AddAcceleration(const Vector2 newAcceleration)
{
    this->acceleration += newAcceleration;
}

void VerletObject::Move(const float dt)
{
    const Vector2 velocity = this->position - this->previousPosition;
    this->previousPosition = this->position;

    this->position = this->previousPosition + velocity  + this->acceleration * dt * dt;
    this->acceleration = {};
}

void VerletObject::ConstrainObject(const Vector2 reference, const float constraint)
{
    const Vector2 distanceToReference = this->position - reference;
    if (Vector2LengthSqr(distanceToReference) > constraint*constraint)
    {
        this->position = reference + Vector2Scale(Vector2Normalize(distanceToReference), constraint);
    }
}
