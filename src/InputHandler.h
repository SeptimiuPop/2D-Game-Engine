#pragma once
#include "Message.h"


class InputHandler{

    private:
        // variables
        std::map<std::string, int> supportedKeys;
        std::map<std::string, int> keyBinds;

        sf::Event sfEvent;
        sf::Keyboard key;
        sf::Mouse mouse;

        // functions
        void initKeys();

    public:
        InputHandler();
        ~InputHandler();

        std::vector<Message> handle_input(sf::RenderWindow* window);
        Message handle_keys();
        Message handle_mouse();
};

