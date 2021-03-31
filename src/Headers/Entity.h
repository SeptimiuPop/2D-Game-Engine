#pragma once
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"

class Entity{

    private:

        std::unique_ptr<InputComponent> input_; 
        std::unique_ptr<PhysicsComponent> physics_; 
        std::unique_ptr<RenderComponent> renderer_; 


    public:
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float x, y;

        
        Entity()
        : acceleration(0,0),
            velocity(0,0),
            x(0), y(0) {}

        Entity(InputComponent, PhysicsComponent, RenderComponent);        

        void update(const float dt, std::shared_ptr<sf::RenderWindow> window);

};
