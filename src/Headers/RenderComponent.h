#pragma once

class Entity;

class RenderComponent
{

private:
    sf::IntRect textureBounds_;
    sf::Sprite sprite;

    static const int NUMBER_OF_FRAMES = 3;
    int frame = 0;
    int counter = 0;

    void setFacing(sf::RenderWindow& window);
    void setDefaulFacing(Entity& player);

public:

    void initComponent(sf::Texture& texture, unsigned width, unsigned height);

    void update(Entity& player, sf::RenderWindow& window);

};
