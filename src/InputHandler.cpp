#include "Includes.h"
#include "InputHandler.h"

    // private methods

    void InputHandler::initKeys(){
        /*Create the game's supported keys list and map them to some key bindings*/

        // Open config file for the supported keys
        std::ifstream config("../config/supported_keys.ini");
        if(config.is_open()){
            std::string key;
            int value;

            // Assign key-value pair for the supported keys
            while(config >> key >> value)
                supportedKeys[key] = value;
        }
        config.close();
        
        // Open config file for keybinds
        config.open("../config/key_binds.ini");
        if(config.is_open()){
            std::string key;
            std::string value;

            // Assign an action to some supported key
            while(config >> key >> value)
                keyBinds[key] = supportedKeys.at(value);
        }
        config.close();
    }

    // public methods

    InputHandler::InputHandler(){initKeys();}
    InputHandler::~InputHandler(){}

    std::vector<Message> InputHandler::handle_input(sf::RenderWindow* window){
        
        input.clear();
        Message mes;


        handle_keys();
        while(window->pollEvent(sfEvent)){
            handle_mouse();
        }

        return input;
    }

    void InputHandler::handle_keys(){
        
        Message mes;

        // Key pressed events
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE")))) {mes.setCheck("CLOSE", true);input.push_back(mes);}
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("SLOW"))))  {mes.setCheck("SLOW", true); input.push_back(mes);}
        
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_UP"))))    {mes.setDir("MOVE", sf::Vector2i( 0,-1)); input.push_back(mes);}
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_LEFT"))))  {mes.setDir("MOVE", sf::Vector2i(-1, 0)); input.push_back(mes);}
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT")))) {mes.setDir("MOVE", sf::Vector2i( 1, 0)); input.push_back(mes);}
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_DOWN"))))  {mes.setDir("MOVE", sf::Vector2i( 0, 1)); input.push_back(mes);}
        if(mouse.isButtonPressed(mouse.Right)) {mes.setCheck("DRAW", true); input.push_back(mes);}           
    }


    void InputHandler::handle_mouse(){
        
        Message mes;
        
        // Key released events
        if(sfEvent.type == sf::Event::KeyReleased){
            // Resize will always be alt+enter so no keybinding set here
            if(sfEvent.key.code == key.Enter && key.isKeyPressed(key.LAlt)) {mes.setCheck("FULLSCREEN", true); input.push_back(mes);} 
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("SLOW")))  {mes.setCheck("SLOW", false); input.push_back(mes);} 
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("NEXT_ANIM")))  {mes.setCheck("NEXT", false); input.push_back(mes);}
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("PREV_ANIM")))  {mes.setCheck("PREV", false); input.push_back(mes);}
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("RESET_ANIM")))  {mes.setCheck("RESET", false); input.push_back(mes);}

            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_UP")))    {mes.setDir("MOVE", sf::Vector2i(0,0)); input.push_back(mes);}
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_LEFT")))  {mes.setDir("MOVE", sf::Vector2i(0,0)); input.push_back(mes);}
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_DOWN")))  {mes.setDir("MOVE", sf::Vector2i(0,0)); input.push_back(mes);}
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT"))) {mes.setDir("MOVE", sf::Vector2i(0,0)); input.push_back(mes);}
        }

        if (sfEvent.type == sf::Event::MouseButtonReleased)
            if (sfEvent.mouseButton.button == mouse.Right)
                {mes.setCheck("DRAW", false);input.push_back(mes);}   
    }