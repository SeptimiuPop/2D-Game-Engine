#include "Includes.h"
#include "Message.h"

    void Message::setText(std::string text){message = text;}
    void Message::setCheck(bool val){check = val;}
    void Message::setDir(std::string act){
        if(act == "UP"   ) {dir.x = 0; dir.y =-1;}
        if(act == "DOWN" ) {dir.x = 0; dir.y = 1;}
        if(act == "LEFT" ) {dir.x =-1; dir.y = 0;}
        if(act == "RIGHT") {dir.x = 1; dir.y = 0;}
    }