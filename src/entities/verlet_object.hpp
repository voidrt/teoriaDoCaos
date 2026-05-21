#pragma once
#include <raymath.h>

class VerletObject
{
    public:
        explicit VerletObject(const Vector2 initialPosition) : position(initialPosition), previousPosition(initialPosition)
        {
        };

        [[nodiscard]] Vector2 GetPosition() const { return this->position; }
        void AddAcceleration(Vector2 newAcceleration);
        void Move(float dt);
        void ConstrainObject(Vector2 reference, float constraint);

    private:
        Vector2 position;
        Vector2 previousPosition;
        Vector2 acceleration{};
};
