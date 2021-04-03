#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/RenderComponent.h"

void RenderComponent::setFacing(sf::RenderWindow& window){
    
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2i view;
    sf::Vector2u window_size = window.getSize();
    view.x =window_size.x/2;
    view.y =window_size.y/2;

    //detects relative pozition to the mouse
    if(abs(mouse.x-view.x) <= abs(mouse.y-view.y)){
        if((mouse.y-view.y)>=0) textureBounds_.top = 1; //mouse up
        else                    textureBounds_.top = 0; //mouse down
    }
    else{
        if((mouse.x-view.x)>=0) textureBounds_.top = 3; //mouse r
        else                    textureBounds_.top = 2; //mouse l
    }
    textureBounds_.top *= textureBounds_.height;
    
}

void RenderComponent::setDefaulFacing(Entity& player){
    
    if (player.velocity.x < 0)      textureBounds_.top = 2 * textureBounds_.height;
    else if (player.velocity.x > 0) textureBounds_.top = 3 * textureBounds_.height;
    else if (player.velocity.y < 0) textureBounds_.top = 0 * textureBounds_.height;
    else if (player.velocity.y > 0) textureBounds_.top = 1 * textureBounds_.height;

}

void RenderComponent::initComponent(sf::Texture& texture, unsigned width, unsigned height){
    sprite.setTexture(texture);
    textureBounds_.width = width;
    textureBounds_.height = height;
    textureBounds_.left = 0;
}

void RenderComponent::update(Entity& player, sf::RenderWindow& window){

    counter++;
    if(counter % 15 == 0){
        counter = 0;
        if(player.velocity == sf::Vector2f(0,0) ||
            frame >= NUMBER_OF_FRAMES)
            frame = 0;
        else
            frame ++;
    }

    textureBounds_.left = frame*textureBounds_.width;
    setFacing(window);
    sprite.setTextureRect(textureBounds_);

    sprite.setPosition(player.x,player.y);
    sprite.setScale(sf::Vector2f(1,1));
    
    window.draw(sprite);
}