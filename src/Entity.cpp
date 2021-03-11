#include "Headers/Includes.h"
#include "Headers/Entity.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

    Entity::Entity(){}

    Entity::Entity(float x_poz, float y_poz)
        :x(x_poz), y(y_poz){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Entity::initSound (sf::SoundBuffer& buffer, float volume, float pitch){
        
        sound.setBuffer(buffer);
        sound.setVolume(volume);
        sound.setPitch(pitch);
    }

    void Entity::initSprite(sf::Texture& texture, float scale, int offset_x, int offset_y){
        rect.height = offset_y;
        rect.width = offset_x;
        rect.left = 0;
        rect.top = 0;
        
        this->scale = scale;

        s.setTexture(texture);
        s.setScale(sf::Vector2f(scale, scale));
        s.setPosition(x,y);

        frame =0;
        index =0;
    }

    sf::Vector2f Entity::getPozition(){
        sf::Vector2f poz;
        poz.x = x+(scale*rect.width)/2;
        poz.y = y+(scale*rect.height)/2;
        return poz;
    }

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Entity::dash(const float & dt){
        if(abs(x-start.x) > 150 || abs(y-start.y) > 150){
            speed = 300;
            state = "Idle";
        }
        else {
            speed += acc;
            x+= dash_dir.x*speed*dt;
            y+= dash_dir.y*speed*dt;
            s.setPosition(x,y);
        }
    }

    void Entity::move(const float & dt, sf::Vector2i dir, bool slowed){
        if(slowed)  speed = 50;
        else if(speed < 300)speed += acc;

        x+= dir.x*speed*dt;
        y+= dir.y*speed*dt;
        s.setPosition(x,y);

    }


    void Entity::play_anim(const float & dt, bool moves){
        
        if(!moves) rect.left = 0;
        
        else{
            //only on certain frames animate the sprite
            de += speed*dt;     // de is the time buffer for the next frame of the animation
            if(de >= 25) {de = 0; rect.left += rect.width;}
            if(rect.left>352) rect.left=0;
        }


        //sets the direction the sprite is facing
        rect.top = facing * rect.height;

    }

    void Entity::update(const float &dt, sf::Vector2i dir, bool slowed, bool check_dash, sf::RenderWindow* window){
     
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

    void Entity::draw(sf::RenderWindow* window, int width, int height){
    
        //if the sprite is out of bounds wrap arround
        // if (x + 128 < 0) x = width; 
        // if (x > width )  x = -128; 
        // if (y + 128 < 0) y = height; 
        // if (y > height)  y = -128; 

        s.setTextureRect(rect);
        window->draw(s);
    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- FACING DIRECTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/

    // Eventually only the player will have this and just store the window pointer inside the class
    // OR COULD EVEN BE AN COMPONENT
    void Entity::setFacing(sf::RenderWindow* window, sf::Vector2i dir){
        if(window != nullptr){
            sf::Vector2i mouse = sf::Mouse::getPosition(*window);
            sf::Vector2i view;
            sf::Vector2u window_size = window->getSize();
            view.x =window_size.x/2;
            view.y =window_size.y/2;

            //detects relative pozition to the mouse
            if(abs(mouse.x-view.x) <= abs(mouse.y-view.y)){
                if((mouse.y-view.y)>=0) facing = 1; //mouse up
                else                    facing = 0; //mouse down
            }
            else{
                if((mouse.x-view.x)>=0) facing = 3; //mouse r
                else                    facing = 2; //mouse l
            }

        }
        else{
            if(dir.y<0) facing = 0;    // 0 up
            if(dir.x<0) facing = 2;    // 2 left
            if(dir.x>0) facing = 3;    // 3 right
            if(dir.y>0) facing = 1;    // 1 down
        }
    }

    void Entity::update_on_target(float target_x, float target_y){
        
        //original sprite position is top left corner
        //adjust pozition to the center
        int sprite_dx = x+64, sprite_dy = y+64;

        //detects relative pozition to the target
        if(abs(target_x-sprite_dx) <= abs(target_y-sprite_dy)){
            if((target_y-sprite_dy)>=0) facing = 1; //target up
            else                        facing = 0; //target down
        }
        else{
            if((target_x-sprite_dx)>=0) facing = 3; //target r
            else                        facing = 2; //target l
        }

    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= ANIMATION FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
    // -> TO BE MOVED IN SEPARATE COMPONENT

    void Entity::next_anim(){
        reset_anim();
        index ++;
        if(index == 13) index = 0;
        rect.top = rect.height*index;
    }
    void Entity::prev_anim(){
        reset_anim();
        index --;
        if(index == -1) index = 12;
        rect.top = rect.height*index;
    }
    void Entity::reset_anim(){
        frame=0;
        rect.left = 0;
    }
    void Entity::animate(const float & dt, bool check){
        if(!animating && check) animating = true;
        if(animating){
            de += dt;
            if(de > 0.1){
                de = 0;
                if(fr[index]<=frame+1){
                    reset_anim();
                    animating = false;
                } 
                else {
                    frame ++;
                    rect.left = rect.width*frame;
                }
            }
        }
    }

    void Entity::play_sound(const float & dt, bool play){
        if(play){
            if(sound_buffer > 150){
                sound_buffer = 0;
                sound.play();
            }
            sound_buffer += speed*dt;
        }
        else sound_buffer = 0;
    }
