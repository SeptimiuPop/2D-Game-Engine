#pragma once
#include "Message.h"


class InputHandler{

    private:
        // variables
        std::shared_ptr<sf::RenderWindow> window;
        
        std::map<std::string, int> supportedKeys;
        std::map<std::string, int> keyBinds;

        std::vector<Message> input;

        sf::Event sfEvent;
        sf::Keyboard key;
        sf::Mouse mouse;

        // functions
        void initKeys();
        void handle_menu_events();
        void handle_game_events();

    public:
        InputHandler(std::shared_ptr<sf::RenderWindow>);
        ~InputHandler();

        std::vector<Message> &getInputs();
        void handle_inputs();
};

