#include "Entity.h"


    Entity::Entity(float x_poz, float y_poz)
        :x(x_poz), y(y_poz){}

    void Entity::initSprite(std::string file, float scale, int offset_x, int offset_y){
        
        size_x = offset_x;
        size_y = offset_y;

        t.loadFromFile(file);
        s.setTexture(t);
        s.setScale(sf::Vector2f(scale, scale));
    }

    void Entity::move(float dx, float dy, bool slowed, float dt){
        
        if(slowed)  speed = 100;
        else        speed = 300;

        if(dx<0) {facing = 0; dir[0] = 1;}
        if(dy<0) {facing = 1; dir[1] = 1;}
        if(dx>0) {facing = 2; dir[2] = 1;}
        if(dy>0) {facing = 3; dir[3] = 1;}

        x+= dx*speed*dt;
        y+= dy*speed*dt;
        s.setPosition(x,y);

        //sets the direction the sprite is facing
        if(facing == 1) iny = 0 ;
        if(facing == 3) iny = 32;
        if(facing == 0) iny = 64;
        if(facing == 2) iny = 96;
    }

    void Entity::updateAnimation(float dt, bool moves){
        
        if(!moves) inx = 0;
        
        else{
        //on certain frames animate the sprite
        de += dt;
        if(de >= 0.05) {de = 0; inx += 32;}
        if(inx>352) inx=0;
        }
    }

    void Entity::update_on_mouse(float target_x, float target_y){
        
        //original sprite position is top left corner
        //adjust pozition to the center
        int sprite_dx = x+64, sprite_dy = y+64;


        //detects relative pozition to the mouse
        if(abs(target_x-sprite_dx) <= abs(target_y-sprite_dy)){
            if((target_y-sprite_dy)>=0) facing = 3; //mouse up
            else                        facing = 1; //mouse down
        }
        else{
            if((target_x-sprite_dx)>=0) facing = 2; //mouse r
            else                        facing = 0; //mouse l
        }
        if(facing == 1) iny = 0 ;
        if(facing == 3) iny = 32;
        if(facing == 0) iny = 64;
        if(facing == 2) iny = 96;
    }

    void Entity::draw(sf::RenderWindow* window, int width, int height){
    
        //if the sprite is out of bounds wrap arround
        // x = int(x+width)%width;
        // y = int(y+height)%height;

        if (x + 64 < 0 ) x = width + 64; 
        if (x - 64 > width ) x = 0 - 64; 
        if (y + 64 < 0) y = height + 64; 
        if (y - 64 > height) y = 0 - 64; 

        s.setTextureRect(sf::IntRect(inx, iny, size_x, size_y));
        window->draw(s);
    }


