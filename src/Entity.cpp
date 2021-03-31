#include "Headers/Includes.h"
#include "Headers/Entity.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


    Entity::Entity(InputComponent input,
                  PhysicsComponent physics,
                  RenderComponent renderer):
        input_   (std::make_unique<InputComponent>  (input)),
        physics_ (std::make_unique<PhysicsComponent>(physics)),
        renderer_(std::make_unique<RenderComponent> (renderer)),
        acceleration(0,0), velocity(0,0), x(0), y(0){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    /*  -- PURGE VETERANS handle with care
    void Entity::initSound (sf::SoundBuffer& buffer, float volume, float pitch){
        
        sound.setBuffer(buffer);
        sound.setVolume(volume);
        sound.setPitch(pitch);
    }

    void Entity::play_sound(const float & dt, bool play){
        if(play){
            if(sound_buffer > 50){
                sound_buffer = 0;
                sound.play();
            }
            sound_buffer += speed*dt;
        }
        else sound_buffer = 0;
    }

    void Entity::dash(const float & dt){
        if(abs(x-start.x) > 50 || abs(y-start.y) > 50){
            speed = 100;
            state = "Idle";
        }
        else {
            
            speed += acc;
            x+= dash_dir.x*speed*dt;
            y+= dash_dir.y*speed*dt;
            s.setPosition(x,y);
        }
    }

    void Entity::update(const float &dt, sf::Vector2i dir, bool slowed, bool check_dash, std::shared_ptr<sf::RenderWindow> window){
     
        if(state == "Dash") dash(dt);

        if(state == "Idle"){
            
            setFacing(window, dir);
            bool moving = false;

            if(dir.x != 0 || dir.y != 0) moving = true;
            
            // dash related matters
            if(check_dash && moving) {
                rect.left = 0;
                state = "Dash";
                start = sf::Vector2f(x,y);
                dash_dir = dir;
            }

            move(dt, dir, slowed);
            play_anim(dt, moving);
            play_sound(dt, moving);
        }
        

    }
    */


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Entity::update(const float dt, std::shared_ptr<sf::RenderWindow> window)
    {
        input_->update(*this);
        physics_->update(*this);
        renderer_->update(*this, *window);
    }


