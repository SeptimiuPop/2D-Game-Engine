#pragma once
#include "Component.h"

class Entity;

class InputComponent: public Component
{
    private:
        const float WALK_ACCELERATION = 1.f;
    
    public:
        void update(Entity& player);

};