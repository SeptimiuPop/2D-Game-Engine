#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/AIComponent.h"

AIComponent::AIComponent(){}

void AIComponent::update(Entity& entity, Entity& player) {
    
    
    if(entity.x <= player.x)
        entity.velocity.x = 1;
    if(entity.x >= player.x)
        entity.velocity.x = -1;
    if(entity.y <= player.y)
        entity.velocity.y = 1;
    if(entity.y >= player.y)
        entity.velocity.y = -1;

}