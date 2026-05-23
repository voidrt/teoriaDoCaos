#pragma once
#include <raymath.h>

class VerletObject
{
    public:
        explicit VerletObject(const float initialAngle) : angle(initialAngle), previousAngle(initialAngle)
        {
        };

        [[nodiscard]] float GetAngle() const { return this->angle; }
        void AddAcceleration(float newAcceleration);
        void Move(float dt);

    private:
        float angle;
        float previousAngle;
        float angularAcceleration = 0;
};
