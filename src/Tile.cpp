#include "Headers/Includes.h"
#include "Headers/Tile.h"

    Tile::Tile(){}
    
    Tile::Tile(sf::Vector2f position):
        pos(position){
            sprite.setPosition(pos);
        }

    void Tile::setTexture(sf::Texture& texture){
        sprite.setTexture(texture);
    }

    void Tile::setTexturePos(sf::IntRect texturePos){
        texture_pos = texturePos;
        sprite.setTextureRect(texture_pos);
    }

    void Tile::draw(sf::RenderWindow& window){
        window.draw(sprite);
    }
