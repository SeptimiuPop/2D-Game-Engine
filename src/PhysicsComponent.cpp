#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/PhysicsComponent.h"

void PhysicsComponent::update(Entity& player, const float dt) {

    
    float newX, newY;
    newX = player.x + player.velocity.x * 100 * dt; 
    newY = player.y + player.velocity.y * 100 * dt;

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

    int height = gameWorld->size()-1;
    int width  = gameWorld->at(1).size()-1;


    if(left_tile < 0) left_tile = 0;
    if(top_tile < 0 ) top_tile  = 0;
    if(right_tile > width ) right_tile  = width;
    if(bottom_tile> height) bottom_tile = height;

    for(int i=left_tile; i<=right_tile; i++){
        for(int j=top_tile; j<=bottom_tile; j++){
            if(gameWorld->at(j)[i].checkBlocked())
                return true;
        }
    }
    return false;
}