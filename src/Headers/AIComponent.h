#pragma once
#include "Component.h"

class Entity;

class AIComponent : public Component 
{
private:
    const float WALK_ACCELERATION = 1.f;

public:
    AIComponent();

    void update(Entity& entity, Entity& player);

};