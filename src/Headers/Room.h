#pragma once
#include "Engine.h"
#include "Entity.h"
#include "Tile.h"

class Room{
    private:
    
        std::shared_ptr<Engine> engine;
        std::vector<std::vector<Tile>> map;
        Entity player;

        sf::View view;

        int height, width;
        int roomCount;


        void initMap(std::string);
        void initPlayer();
        void spawnEntities();
    public:
    
        Room();

        ~Room();

        void setEngine(std::shared_ptr<Engine>);
        void generateRoom();
        void UpdateView();

        void Update(const float dt);
        void Draw(const float dt);

};



/*
    void Game::initEntities(){
        
        
        for(int i=0; i<3; i++){
            Entity en(i*200,0);
            entities.push_back(en);
        }

        // entities[0].initSprite(engine->_assets->getTexture("bg"), 2, 1920, 1088);
        entities[1].initSprite(engine->_assets->getTexture("mo"), 1, 100, 64);
        entities[2].initSprite(engine->_assets->getTexture("pl"),1,16,32);
        
        // sound
        entities[2].initSound(engine->_assets->getSound("walk_stone"), 60.f, 1.f);
    }


    void Game::Render(){  
        // draw game elements in view
        engine->_window->setView(view);
        room.draw();
        for(auto& en:entities) 
            en.draw(engine->_window);
        

        // draw UI elements
        engine->_window->setView(engine->_window->getDefaultView());
        for(auto& en:ui) 
            en.draw(engine->_window);
        }



    // PART OF THE UI -- SHOULD MOVE IT NOW THAT WINDOW DOESN'T BELONG TO THE GAME
    void Game::UpdateView(){

        // Sets the view of the window around the player 
        
        sf::Vector2i cursor = sf::Mouse::getPosition(*engine->_window);
        sf::Vector2f player = sf::Vector2f(entities[2].x, entities[2].y);

        // center the mouse position
        cursor.x -= engine->_window->getSize().x/2;
        cursor.y -= engine->_window->getSize().y/2;
        
        // set the view position to be centered on the player
        // plus a small offset given by the mouse pozition
        sf::Vector2f view_bounds;
        view_bounds.x = player.x + (cursor.x)/32;
        view_bounds.y = player.y + (cursor.y)/16;

        view.setCenter(view_bounds);
    }


*/