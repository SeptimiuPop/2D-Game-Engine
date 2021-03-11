#include "Headers/Includes.h"
#include "Headers/Tile.h"

    Tile::Tile(sf::Vector2i position, bool blocked):
        pos(position), isBlocked(blocked){}


    void Tile::setTexturePos(sf::IntRect texturePos){
        layers.push_back(texturePos);
    }

    sf::IntRect& Tile::getTexturePos(){
        return layers[0];
    }