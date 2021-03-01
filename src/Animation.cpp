#include "Animation.h"

    Animation::Animation(){}
    void Animation::initFile(std::string file_name){
        texture.loadFromFile(file_name);
        sprite.setTexture(texture);
    }