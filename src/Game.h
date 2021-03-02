#pragma once
#include "Entity.cpp"

class Game{

    private:
        //variables
        sf::RenderWindow *window;
        sf::Event sfEvent;
        sf::Keyboard key;
        sf::Mouse mouse;
        std::vector<Entity> entities;
        sf::View view; 

        std::map<std::string, int> supportedKeys;
        std::map<std::string, int> keyBinds;

        sf::Clock dtClock;
        float dt;

        int width;
        int height;
        

        bool fullscreen = true;
        bool slowed = false;
        bool move = false;
        bool draw   = false;
        bool clear  = true;
        
        int dir[4] = {0,0,0,0};

        //initialization
        void initWindow();
        void initKeys();
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
