#pragma once
#include "AIComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class Entity{

    private:

        InputComponent input_; 
        PhysicsComponent physics_; 
        RenderComponent renderer_; 


    public:
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float x, y;

        
        Entity()
        : acceleration(0,0),
            velocity(0,0),
            x(0), y(0) {}

        Entity(std::shared_ptr<Engine> engine, std::vector<std::vector<Tile>>* map);   

        void update(const float dt, std::shared_ptr<sf::RenderWindow> window);

};
