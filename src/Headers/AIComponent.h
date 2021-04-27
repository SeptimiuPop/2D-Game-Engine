#pragma once

class Entity;

class AIComponent
{
private:
    const float WALK_ACCELERATION = 1.f;

public:
    AIComponent();

    void update(Entity& entity, Entity& player);

};