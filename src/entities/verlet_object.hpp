#pragma once
#include <raymath.h>

class VerletObject
{
    public:
        explicit VerletObject(const float initialAngle) : m_angle(initialAngle), m_previousAngle(initialAngle)
        {
        };

        [[nodiscard]] float GetAngle() const { return this->m_angle; }
        void AddAcceleration(float newAcceleration);
        void Move(float dt);
        void Reset(float initialAngle);

    private:
        float m_angle;
        float m_previousAngle;
        float m_angularAcceleration = 0;
};
