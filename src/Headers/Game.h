#pragma once
#include "Entity.h"
#include "InputHandler.h"
#include "ResourceManager.h"
#include "Map.h"

struct Engine{

    std::shared_ptr<sf::RenderWindow> _window;
    std::unique_ptr<ResourceManager> _assets;
    std::unique_ptr<InputHandler> _inputs;

    Engine(){
        _window = std::make_shared<sf::RenderWindow>();
        _assets = std::make_unique<ResourceManager>();
        _inputs = std::make_unique<InputHandler>();
    }

};



class Game{

    private:

        //variables
        std::shared_ptr<Engine> engine;

        
        sf::RenderWindow *window;
        sf::View view; 
        int width;
        int height; 
        bool fullscreen = true;

        Map map;

        std::vector<Entity> ui;
        std::vector<Entity> entities;
        

        sf::Clock dtClock;
        float dt;
        const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

        sf::Music music;


        //initialization functions
        void initWindow();
        void initBgMusic();
        void initEntities();
        void initUIElements();
        void changeVideoMode();

    public:

        //constructior/destructior
        Game();
        virtual ~Game();

        //update functions
        void UpdatePlayerEvents();
        void UpdateView();
        void Update();
        void Render();
        void Run();

};
