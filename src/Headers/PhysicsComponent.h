#pragma once
#include "Tile.h"

class Entity;

class PhysicsComponent
{
private:
    const float WALKING_DECELERATION = 1.f;
    const float WALKING_ACCELERATION = 1.f;
    const int MAX_SPEED = 20;

    std::vector<std::vector<Tile>>* gameWorld;

    bool tile_collision(float x, float y);

public:

    PhysicsComponent(std::vector<std::vector<Tile>>* world):
        gameWorld(world){}

    void update(Entity& player, const float dt);

};