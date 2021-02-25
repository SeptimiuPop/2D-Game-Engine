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

        sf::Texture bg_t;
        sf::Sprite bg_s;

        sf::Clock dtClock;
        float dt;

        int width;
        int height;
        

        bool fullscreen = true;
        bool slowed = false;
        bool move = false;
        bool draw   = false;
        bool clear  = true;
        
        //initialization
        void initWindow();

    public:

        //constructior/destructior
        Game();
        virtual ~Game();

        //function
        void UpdateSFMLEvents();
        void UpdateMovement();
        void update();
        void render();
        void run();

};
