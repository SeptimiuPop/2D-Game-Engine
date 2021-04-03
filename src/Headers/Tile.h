#pragma once

class Tile{

    private:
    
    sf::Sprite sprite;
    sf::Vector2f pos;
    sf::IntRect texture_pos;

    bool isBlocked;


    public:
        Tile();
        Tile(sf::Vector2f, bool);
        
        void setTexture(sf::Texture&);
        void setTexturePos(sf::IntRect);        
    
        void draw(sf::RenderWindow&);



};
