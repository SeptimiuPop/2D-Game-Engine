#pragma once
#include "Entity.h"
#include "InputHandler.h"

class Game{

    private:
        //variables
        sf::RenderWindow *window;
        sf::View view; 
        bool fullscreen = true;

        std::vector<Entity> entities;
        
        InputHandler handler;
        sf::Event sfEvent;
        sf::Keyboard key;
        sf::Mouse mouse;

        sf::Clock dtClock;
        float dt;

        int width;
        int height; 

        //initialization
        void initWindow();
        void initEntities();
        void changeVideoMode();

    public:

        //constructior/destructior
        Game();
        virtual ~Game();

        //function
        void UpdateSFMLEvents();
        void UpdateMovement();
        void UpdateView();
        void update();
        void render();
        void run();

};
