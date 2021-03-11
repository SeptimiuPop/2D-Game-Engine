#pragma once
#include "Tile.h"

class Map{
    private:
    
        std::vector<std::vector<Tile>> map;
        int height, width;
        int roomCount;


        void initMap();

    public:
    
        Map();
        ~Map();

        void generateRoom();

        void draw(sf::RenderWindow* window, sf::Texture& tx);

};
