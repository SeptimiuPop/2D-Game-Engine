#include "Entity.h"


    Entity::Entity(float x_poz, float y_poz)
        :x(x_poz), y(y_poz){}

    void Entity::initSprite(std::string file){
        t.loadFromFile(file);
        s.setTexture(t);
        s.setScale(sf::Vector2f(4.f, 4.f));
    }

    float Entity::get_x_pozition(){
        return x;
    }

    float Entity::get_y_pozition(){
        return y;
    }

    void Entity::move(float dx, float dy){
        // if(speed <= 20) speed += acc;
        if(dx<0) {facing = 0; dir[0] = 1;}
        if(dy<0) {facing = 1; dir[1] = 1;}
        if(dx>0) {facing = 2; dir[2] = 1;}
        if(dy>0) {facing = 3; dir[3] = 1;}

        // if(slowed) speed = 5; else speed = 1;

        x+= dx*speed;
        y+= dy*speed;
        s.setPosition(x,y);

        //sets the direction the sprite is facing
        if(facing == 1) iny = 0 ;
        if(facing == 3) iny = 32;
        if(facing == 0) iny = 64;
        if(facing == 2) iny = 96;

        //on certain frames animate the sprite
        de = (de+1)%16;
        if(de==0) inx += 32;
        if(inx>352) inx=0;
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

    void Entity::resetSpeed(){speed=3;}

    void Entity::draw(sf::RenderWindow* window, int width, int height){
        // if(x<0||x>width) x = int(width+x)%width;
        // if(y<0||y>height) y = int(height+y)%height;

    
        //if the sprite is out of bounds wrap arround
        // dx = (dx+width)%width;
        // dy = (dy+height)%height;

        s.setTextureRect(sf::IntRect(inx, iny, tx, ty));
        window->draw(s);
    }


