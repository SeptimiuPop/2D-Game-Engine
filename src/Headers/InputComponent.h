#pragma once
#include "Engine.h"

class Entity;

class InputComponent
{
private:
    const float WALK_ACCELERATION = 1.f;
    std::shared_ptr<Engine> engine;

public:
    InputComponent(std::shared_ptr<Engine> game_engine):
        engine(game_engine){}

    void update(Entity& player);

};