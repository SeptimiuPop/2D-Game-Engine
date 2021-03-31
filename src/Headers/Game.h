#pragma once
#include "Engine.h"
#include "Room.h"
#include "GameMenu.h"

class Game{

    private:

        //variables
        std::shared_ptr<Engine> engine;

        sf::View view; 
        bool fullscreen = true;

        Room room;
        GameMenu menu;

        sf::Clock dtClock;
        float dt;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

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
