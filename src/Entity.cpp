#include "Headers/Includes.h"
#include "Headers/Entity.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


    Entity::Entity(std::shared_ptr<Engine> engine, std::vector<std::vector<Tile>>* map):
        acceleration(0,0), velocity(0,0), x(0), y(0){
            input_.Init(engine);
            physics_.Init(map);
            renderer_.initComponent(engine->_assets->getTexture("player"), 16, 32);
        }



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Entity::update(const float dt, std::shared_ptr<sf::RenderWindow> window){
        // input_.update(*this);
        // physics_.update(*this, dt);
        renderer_.update(*this, *window);

    }


