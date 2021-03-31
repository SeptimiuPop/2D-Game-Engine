#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/PhysicsComponent.h"

void PhysicsComponent::update(Entity& player){
    

    // if(player.velocity.x == 0){
    //     if(player.acceleration.x < 0)
    //         player.acceleration.x += WALKING_DECELERATION;
    //     if(player.acceleration.x > 0)
    //         player.acceleration.x -= WALKING_DECELERATION;
    // }
    // if(player.velocity.y == 0){
    //     if(player.acceleration.y < 0)
    //         player.acceleration.y += WALKING_DECELERATION;
    //     if(player.acceleration.y > 0)
    //         player.acceleration.y -= WALKING_DECELERATION;
    // }
    
    // if(abs(player.acceleration.x) <= MAX_SPEED)
    // player.acceleration.x += player.velocity.x * WALKING_ACCELERATION;
    // if(abs(player.acceleration.y) <= MAX_SPEED)
    // player.acceleration.y += player.velocity.y * WALKING_ACCELERATION;

    // player.x += player.acceleration.x;
    // player.y += player.acceleration.y;

    player.x += player.velocity.x * 5;
    player.y += player.velocity.y * 5;
    
    player.x = int(1200 + player.x)%1200;
    player.y = int (600 + player.y) %600;

}