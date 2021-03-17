#pragma once

class Entity{

    private:
        std::string state = "Idle";

        sf::Sprite s;
        sf::IntRect rect;

        sf::Sound sound;
        float sound_buffer;


        sf::Vector2i dash_dir;
        sf::Vector2f start;
        
        float de=0;
        int facing=0;

        float scale;
        float x;
        float y;
        float speed=100;
        float acc= 1;

        // FOR ANIMATION -> TO BE MOVED IN SEPARATE COMPONENT
        bool animating = false;
        int index;
        int frame;
        int fr[13] = {6,8,3,3,6,9,18,25,16,6,13,7,18};
        // int fr[17] = {17,17,17,17,17,17,17,17,17,17,17,17,17};

    public:
        Entity();
        Entity(float x, float y);
    
        void initSound(sf::SoundBuffer& buffer, float volume, float pitch);
        void initSprite(sf::Texture& texture, float scale, int offset_x, int offset_y);
        sf::Vector2f getPozition();

        void dash(const float & dt);

        void move(const float & dt, sf::Vector2i dir, bool slowed);
        void setFacing(std::shared_ptr<sf::RenderWindow> window, sf::Vector2i dir);
        void play_anim(const float & dt, bool moves);
        void play_sound(const float & dt, bool play);
        
        void update(const float &dt, sf::Vector2i dir, bool slowed, bool dash, std::shared_ptr<sf::RenderWindow> window);
        void draw(std::shared_ptr<sf::RenderWindow> window);

        // FOR FACING DIRECTION 
        void update_on_target(float mouse_x, float mouse_y);
        void update_on_mouse(sf::Vector2i screen_center, sf::Vector2i mouse_poz);


        // FOR ANIMATION -> TO BE MOVED IN SEPARATE COMPONENT
        void next_anim();
        void prev_anim();
        void reset_anim();
        void animate(const float & dt, bool check);
};
