#pragma once 
#include "Engine.h"
#include "Button.h"

class GameMenu{
    
    private:

        std::shared_ptr<Engine> engine;

        std::vector<std::string> actions;
        std::vector<Button> buttons;
        
        sf::Text menu_message;

        int selected = 0;

        void InitMessage();
        void InitActions();
        void InitButtons();

    public:

        GameMenu();
        
        void setEngine(std::shared_ptr<Engine>);
        void Init();

        void Update();
        void Draw();
};
