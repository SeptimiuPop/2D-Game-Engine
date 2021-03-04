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

    void InputHandler::handle_input(sf::RenderWindow* window){
        // while(window->pollEvent(sfEvent))
        Message mes = handle_keys();
    }

    Message InputHandler::handle_keys(){
        
        Message mes;

        // Key pressed events
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE")))) mes.setText("CLOSE");
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_UP")))) mes.setText("MOVE");
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_LEFT")))) mes.setText("MOVE");
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_DOWN")))) mes.setText("MOVE");
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT")))) mes.setText("MOVE");
        if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("SLOW")))) mes.setText("SLOW");
        


        // Key released events
        if(sfEvent.type == sf::Event::KeyReleased){
            // Resize will always be alt+enter so no keybinding set here
            if (sfEvent.key.code == key.Enter 
                && key.isKeyPressed(key.LAlt)) mes.setText("FULLSCREEN"); 

            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_UP"))) mes.setText("MOVE");
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_LEFT"))) mes.setText("MOVE");
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_DOWN"))) mes.setText("MOVE");
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("MOVE_RIGHT"))) mes.setText("MOVE");
            if(sfEvent.key.code == sf::Keyboard::Key(keyBinds.at("SLOW"))) mes.setText("SLOW");
        }
        
        return mes;
    }


    int InputHandler::handle_mouse(){
        
        if(mouse.isButtonPressed(mouse.Right)) return 1;

        if (sfEvent.type == sf::Event::MouseButtonReleased)
            if (sfEvent.mouseButton.button == mouse.Right)
                return 2;
        
        return 0;
    }