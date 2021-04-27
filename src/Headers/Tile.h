#pragma once

class Tile{

    private:
    
    sf::Sprite sprite;
    sf::Vector2f pos;
    sf::IntRect texture_pos;

    bool isBlocked;


    public:
        Tile();
        Tile(sf::Vector2f);
        
        bool checkBlocked() {
            return isBlocked;
        }

        void setBlocking(bool blocking) {
            isBlocked = blocking;
        }

        void setTexture(sf::Texture&);
        void setTexturePos(sf::IntRect);        
    
        void draw(sf::RenderWindow&);



};
