#include "Headers/Includes.h"
#include "Headers/Message.h"

    void Message::setCheck(std::string text, bool val){
        message = text;
        check = val;
    }

    void Message::setDir(std::string text, sf::Vector2i direction){
        message = text;
        dir.x += direction.x;
        dir.y += direction.y;

    }
