#pragma once
#include "Includes.h"

class Message{
    
    public:

    std::string message;
    bool check;
    sf::Vector2i dir;

    void setText(std::string text);
    void setCheck(bool val);
    void setDir(std::string act);
};