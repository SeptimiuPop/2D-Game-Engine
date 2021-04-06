#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/PhysicsComponent.h"

void PhysicsComponent::update(Entity& player) {

    
    float newX, newY;
    newX = player.x + player.velocity.x * 1.5; 
    newY = player.y + player.velocity.y * 1.5;

    bool col;

    col = tile_collision(newX, player.y);
    if(!col)
        player.x = newX;

    col = tile_collision(player.x, newY);
    if(!col)
        player.y = newY;
    
}

/* Collision detection based on game tiles
 * Detects blocked tiles close to the entity  
 * https://jonathanwhiting.com/tutorial/collision/
 */
bool PhysicsComponent::tile_collision(float x, float y){
    
    int left_tile   = (x-7)/16;
    int right_tile  = (x+7)/16;
    int top_tile    = (y)/16;
    int bottom_tile = (y+8)/16;

    if(left_tile < 0) left_tile = 0;
    if(top_tile < 0) top_tile = 0;
    if(right_tile > gameWorld->size()-1) right_tile = gameWorld->size()-1;
    if(bottom_tile > gameWorld->at(1).size()-1) bottom_tile = gameWorld->at(1).size()-1;

    for(int i=left_tile; i<=right_tile; i++){
        for(int j=top_tile; j<=bottom_tile; j++){
            if(gameWorld->at(i)[j].checkBlocked())
                return true;
        }
    }
    return false;
}