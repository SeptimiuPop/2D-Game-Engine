#pragma once
#include "Entity.h"
#include "InputHandler.h"

class Game{

    private:
        //variables
        sf::RenderWindow *window;
        sf::View view; 
        int width;
        int height; 
        bool fullscreen = true;

        std::vector<Entity> entities;
        InputHandler handler;

        sf::Clock dtClock;
        float dt;

        sf::Music music;

        std::string state;

        //initialization functions
        void initWindow();
        void initBgMusic();
        void initEntities();
        void changeVideoMode();

    public:

        //constructior/destructior
        Game();
        virtual ~Game();

        //update functions
        void UpdatePlayerEvents();
        void UpdateView();
        void update();
        void render();
        void run();

};
