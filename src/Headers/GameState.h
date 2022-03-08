#pragma once
#include "Engine.h"
#include "Entity.h"
#include "Component.h"
#include "Tile.h"


class GameState{
    private:
    
        std::shared_ptr<Engine> engine;
        std::vector<std::vector<Tile>> map;

        std::vector<Entity> enemies;
        Entity player;

        sf::View view;

        int height, width;
        int roomCount;


        void initMap(std::string);
        void initPlayer();
        void spawnEntities();
        
    public:
    
        GameState();

        ~GameState();

        void setEngine(std::shared_ptr<Engine>);
        void generateRoom();
        void UpdateView();

        void Update(const float dt);
        void Draw(const float dt);

};


