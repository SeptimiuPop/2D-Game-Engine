#pragma once
#include "Animation.h"

class Entity{

    private:
        sf::Texture t;
        sf::Sprite s;
        sf::IntRect rect;

        sf::SoundBuffer buffer;
        sf::Sound sound;
        float sound_buffer;

        float de=0;
        int facing=0;

        float scale;
        float x;
        float y;
        float speed=300;
        float acc= 0.5;

        // FOR ANIMATION -> TO BE MOVED IN SEPARATE COMPONENT
        int index;
        int frame;
        int fr[13] = {6,8,3,3,6,9,18,25,16,6,13,7,18};
        // int fr[17] = {17,17,17,17,17,17,17,17,17,17,17,17,17};

    public:
        Entity();
        Entity(float x, float y);
    
        sf::Vector2f getPozition();

        void initSound();
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
        void play_sound(const float & dt, bool play);
};
