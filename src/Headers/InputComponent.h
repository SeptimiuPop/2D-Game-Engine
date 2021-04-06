#pragma once
#include "Component.h"
#include "Engine.h"

class Entity;

class InputComponent : public Component
{
private:
    const float WALK_ACCELERATION = 1.f;
    std::shared_ptr<Engine> engine;

public:
    InputComponent(std::shared_ptr<Engine> game_engine):
        engine(game_engine){}

    void update(Entity& player);

};