#include "Includes.h"
#include "Message.h"

    void Message::setCheck(std::string text, bool val){
        message = text;
        check = val;
    }

    void Message::setCheckMouse(std::string text, bool val){
        mouse = text;
        check = val;
    }

    void Message::setDir(std::string text, sf::Vector2i direction){
        message = text;
        dir.x = direction.x;
        dir.y = direction.y;
    }