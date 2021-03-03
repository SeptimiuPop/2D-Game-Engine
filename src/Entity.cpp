#include "Entity.h"


    Entity::Entity(float x_poz, float y_poz)
        :x(x_poz), y(y_poz){}

    void Entity::initSprite(std::string file, float scale, int offset_x, int offset_y){
        rect.height = offset_y;
        rect.width = offset_x;
        rect.left = 0;
        rect.top = 0;
        
        this->scale = scale;

        t.loadFromFile(file);
        s.setTexture(t);
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

    void Entity::move(float dx, float dy, bool slowed,const float & dt){
        
        if(slowed)  speed = 50;
        else if(speed < 300)speed += acc;

        if(dx<0) facing = 0;
        if(dy<0) facing = 1;
        if(dx>0) facing = 2;
        if(dy>0) facing = 3;
        
        x+= dx*speed*dt;
        y+= dy*speed*dt;
        s.setPosition(x,y);

    }

    void Entity::updateAnimation(const float & dt, bool moves){
        
        if(!moves) rect.left = 0;
        
        else{
        //on certain frames animate the sprite
        de += speed*dt;
        if(de >= 25) {de = 0; rect.left += rect.width;}
        if(rect.left>352) rect.left=0;
        }

        //sets the direction the sprite is facing
        if(facing == 1) rect.top = 0;
        if(facing == 3) rect.top = rect.height;
        if(facing == 0) rect.top = 2*rect.height;
        if(facing == 2) rect.top = 3*rect.height;
    }

    void Entity::update_on_mouse(sf::Vector2i view, sf::Vector2i mouse){
        
        //detects relative pozition to the mouse
        if(abs(mouse.x-view.x) <= abs(mouse.y-view.y)){
            if((mouse.y-view.y)>=0) facing = 3; //mouse up
            else                        facing = 1; //mouse down
        }
        else{
            if((mouse.x-view.x)>=0) facing = 2; //mouse r
            else                        facing = 0; //mouse l
        }
    }

    void Entity::update_on_target(float target_x, float target_y){
        
        //original sprite position is top left corner
        //adjust pozition to the center
        int sprite_dx = x+64, sprite_dy = y+64;

        //detects relative pozition to the target
        if(abs(target_x-sprite_dx) <= abs(target_y-sprite_dy)){
            if((target_y-sprite_dy)>=0) facing = 3; //target up
            else                        facing = 1; //target down
        }
        else{
            if((target_x-sprite_dx)>=0) facing = 2; //target r
            else                        facing = 0; //target l
        }

    }

    void Entity::draw(sf::RenderWindow* window, int width, int height){
    
        //if the sprite is out of bounds wrap arround
        if (x + 128 < 0) x = width; 
        if (x > width )  x = -128; 
        if (y + 128 < 0) y = height; 
        if (y > height)  y = -128; 


        s.setTextureRect(rect);
        window->draw(s);
    }


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
    void Entity::animate(const float & dt){
        de += dt;
        if(de > 0.1){
            de = 0;
            if(fr[index]<=frame+1) reset_anim();
            else {
                frame ++;
                rect.left = rect.width*frame;
            }
        }
    }