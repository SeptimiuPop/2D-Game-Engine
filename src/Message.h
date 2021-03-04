#pragma once

class Message{
    
    public:

    std::string message;
    std::string mouse;
    sf::Vector2i dir;
    bool check = true;

    void setCheck(std::string text, bool val);
    void setCheckMouse(std::string text, bool val);
    void setDir(std::string text, sf::Vector2i direction);
};