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

    public:
        InputHandler(std::shared_ptr<sf::RenderWindow>);
        ~InputHandler();

        std::vector<Message> &handle_input();
        void handle_press_events();
        void handle_release_events();
};

