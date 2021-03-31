#pragma once
#include "Component.h"

class Entity;

class PhysicsComponent: public Component
{
    private:
        const float WALKING_DECELERATION = 1.f;
        const float WALKING_ACCELERATION = 1.f;
        const int MAX_SPEED = 20;

    public:
        void update(Entity& player);

};