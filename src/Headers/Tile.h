#pragma once

class Tile{

    private:
    
    std::vector<sf::IntRect> layers;
    sf::Vector2i pos;
    bool isBlocked;


    public:

    Tile(sf::Vector2i position, bool blocked);
    
    void setTexturePos(sf::IntRect texturePos);
    
    sf::IntRect& getTexturePos();
    
    



};
