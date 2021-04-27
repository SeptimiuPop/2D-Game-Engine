#pragma once
#include "Engine.h"
#include "GameState.h"
#include "MenuState.h"

class Game{

    private:

        //variables
        std::shared_ptr<Engine> engine;

        GameState scene;
        MenuState menu;

        bool fullscreen = true;

        sf::Clock dtClock;
        float dt;


        //initialization functions
        void initWindow();
        void initBgMusic();
        void setVideoMode();

    public:

        //constructior/destructior
        Game();
        virtual ~Game();

        //update functions
        void UpdatePlayerEvents();
        void Update();

        void Render();
        
        void Run();

};
