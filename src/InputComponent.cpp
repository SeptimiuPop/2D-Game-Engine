#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/InputComponent.h"

    void InputComponent::update(Entity& player){
        
        player.velocity.x = 0;
        player.velocity.y = 0;

        // Apply user input to hero's velocity.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            player.velocity.x -= WALK_ACCELERATION;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            player.velocity.x += WALK_ACCELERATION;
     
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            player.velocity.y -= WALK_ACCELERATION;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            player.velocity.y += WALK_ACCELERATION;
    }