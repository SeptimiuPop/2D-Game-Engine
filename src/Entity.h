#pragma once
#include "Includes.h"

class Entity{

    private:
        sf::Texture t;
        sf::Sprite s;

        int inx = 0, iny = 0, size_x, size_y;

        float de=0;
        int facing=0;

        float x;
        float y;
        float speed=1;
        float acc=0.5;
        int dir[4] = {0,0,0,0};

    public:

    Entity(float x, float y);

    void move(float dx, float dy, bool slowed, float dt);
    
    void updateAnimation(float dt, bool moves);

    void initSprite(std::string file, float scale, int offset_x, int offset_y);

    void update_on_mouse(float mouse_x, float mouse_y);

    void draw(sf::RenderWindow* window, int width, int height);

};
