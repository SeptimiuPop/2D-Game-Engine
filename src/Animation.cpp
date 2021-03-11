#include "Headers/Includes.h"
#include "Headers/Animation.h"

    Animation::Animation(){}
    
    void Animation::initFile(std::string file_name){
        texture.loadFromFile(file_name);
        sprite.setTexture(texture);
    }