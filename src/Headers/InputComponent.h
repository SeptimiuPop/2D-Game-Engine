#pragma once
#include "Engine.h"
#include "Component.h"

class Entity;

class InputComponent : public Component
{
private:
    const float WALK_ACCELERATION = 1.f;
    std::shared_ptr<Engine> engine;

public:
    InputComponent(){}
    
    void Init(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
    }

    void update(Entity& player);

};