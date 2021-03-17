#pragma once
#include "Engine.h"
#include "Tile.h"

class Room{
    private:
    
        std::shared_ptr<Engine> engine;

        std::vector<std::vector<Tile>> map;
        int height, width;
        int roomCount;


        void initMap();

    public:
    
        Room();
        ~Room();

        void setEngine(std::shared_ptr<Engine> engine);
        
        void generateRoom();

        void draw();

};
