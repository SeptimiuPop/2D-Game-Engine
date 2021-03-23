#pragma once

class Message{
    
    public:

    std::string message;
    sf::Vector2i dir;
    bool check = true;

    void setCheck(std::string text, bool val);
    void setDir(std::string text, sf::Vector2i direction);
};