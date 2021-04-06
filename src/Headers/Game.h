#pragma once
#include "Engine.h"
#include "Room.h"
#include "GameMenu.h"

class Game{

    private:

        //variables
        std::shared_ptr<Engine> engine;

        Room room;
        GameMenu menu;

        bool fullscreen = true;

        sf::Clock dtClock;
        float dt;

        sf::Music music;


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
