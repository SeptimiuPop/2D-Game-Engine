#pragma once
#include "Message.h"


class InputHandler{

    private:
        // variables
        std::map<std::string, int> supportedKeys;
        std::map<std::string, int> keyBinds;

        std::vector<Message> input;

        sf::Event sfEvent;
        sf::Keyboard key;
        sf::Mouse mouse;

        // functions
        void initKeys();

    public:
        InputHandler();
        ~InputHandler();

        std::vector<Message> handle_input(sf::RenderWindow* window);
        void handle_keys();
        void handle_mouse();
};

