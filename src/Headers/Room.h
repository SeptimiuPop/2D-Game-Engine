#pragma once
#include "Tile.h"

class Room{
    private:
    
        std::vector<std::vector<Tile>> map;
        int height, width;
        int roomCount;


        void initMap();

    public:
    
        Room();
        ~Room();

        void generateRoom();

        void draw(std::shared_ptr<sf::RenderWindow> window, sf::Texture& tx);

};
