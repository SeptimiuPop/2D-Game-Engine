#pragma once
#include "Includes.h"

class Entity{

    private:
        sf::Texture t;
        sf::Sprite s;

        int inx = 0, iny = 0, tx = 32, ty = 32;

        int de=0;
        int facing=0;

        float x;
        float y;
        float speed=1;
        float acc=0.5;
        bool back = true;
        int dir[4] = {0,0,0,0};

    public:

    Entity(float x, float y);

    float get_x_pozition();
    float get_y_pozition();

    void move(float dx, float dy);

    void initSprite(std::string file);

    void update_on_mouse(float mouse_x, float mouse_y);

    void resetSpeed();

    void draw(sf::RenderWindow* window, int width, int height);

};
