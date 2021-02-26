#pragma once
#include "Includes.h"

class Entity{

    private:
        sf::Texture t;
        sf::Sprite s;
        sf::IntRect rect;

        int size_x, size_y;

        float de=0;
        int facing=0;

        float x;
        float y;
        float speed=300;
        float acc= 0.5;

        int index;
        int frame;
        int fr[13] = {6,8,3,3,6,9,18,25,16,6,13,7,18};

    public:

    Entity(float x, float y);

    void move(float dx, float dy, bool slowed, float dt);
    

    void updateAnimation(float dt, bool moves);

    void initSprite(std::string file, float scale, int offset_x, int offset_y);

    void update_on_mouse(float mouse_x, float mouse_y);

    void draw(sf::RenderWindow* window, int width, int height);

    void next_anim();
    void prev_anim();
    void reset_anim();
    void animate(float dt);
};
