#pragma once


class Animation{
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::IntRect rect;

        int frames[13];
        int index, frame;

    
    public:

    Animation();
    void initFile(std::string file_name);
};