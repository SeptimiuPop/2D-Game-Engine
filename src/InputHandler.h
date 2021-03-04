#pragma once
#include "Message.cpp"


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

        void handle_input(sf::RenderWindow* window);
        Message handle_keys();
        int handle_mouse();
};

