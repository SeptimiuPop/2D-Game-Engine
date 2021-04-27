#pragma once
#include <SFML/Window.hpp>
#include "AudioEngine.h"
#include "InputHandler.h"
#include "ResourceManager.h"

struct Engine{
    
    std::string game_state;
    std::shared_ptr<sf::RenderWindow> _window;
    std::unique_ptr<AudioEngine> _audio;
    std::unique_ptr<ResourceManager> _assets;
    std::unique_ptr<InputHandler> _inputs;

    Engine(){
        _window = std::make_shared<sf::RenderWindow>();
        _audio = std::make_unique<AudioEngine>();
        _assets = std::make_unique<ResourceManager>();
        _inputs = std::make_unique<InputHandler>(_window);
    }

};
