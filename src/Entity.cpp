#include "Headers/Includes.h"
#include "Headers/Entity.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*/


    Entity::Entity(InputComponent input,
                //   AIComponent ai,
                  PhysicsComponent physics,
                  RenderComponent renderer):
        // ai_      (std::make_unique<AIComponent>     (ai)),
        input_   (std::make_unique<InputComponent>  (input)),
        physics_ (std::make_unique<PhysicsComponent>(physics)),
        renderer_(std::make_unique<RenderComponent> (renderer)),
        acceleration(0,0), velocity(0,0), x(0), y(0){}



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Entity::update(const float dt, std::shared_ptr<sf::RenderWindow> window)
    {
        input_->update(*this);
        physics_->update(*this, dt);
        renderer_->update(*this, *window);
    }


