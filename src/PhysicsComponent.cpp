#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/PhysicsComponent.h"

void PhysicsComponent::update(Entity& player){
    
    player.x += player.velocity.x * 1.5;
    player.y += player.velocity.y * 1.5;
    
}