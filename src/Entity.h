#pragma once
#include "Animation.h"

class Entity{

    private:
        sf::Texture t;
        sf::Sprite s;
        sf::IntRect rect;

        float de=0;
        int facing=0;

        float scale;
        float x;
        float y;
        float speed=300;
        float acc= 0.5;

        int index;
        int frame;
        int fr[13] = {6,8,3,3,6,9,18,25,16,6,13,7,18};
        // int fr[17] = {17,17,17,17,17,17,17,17,17,17,17,17,17};

    public:
        Animation animation;

        Entity();
        Entity(float x, float y);
    
        sf::Vector2f getPozition();

        void initSprite(std::string file, float scale, int offset_x, int offset_y);
        void move(float dx, float dy, bool slowed,const float & dt);
        void updateAnimation(const float & dt, bool moves);
        void update_on_target(float mouse_x, float mouse_y);
        void update_on_mouse(sf::Vector2i screen_center, sf::Vector2i mouse_poz);
        void draw(sf::RenderWindow* window, int width, int height);
    
        void next_anim();
        void prev_anim();
        void reset_anim();
        void animate(const float & dt);
};
