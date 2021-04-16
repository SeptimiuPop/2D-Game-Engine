#include "Headers/Includes.h"
#include "Headers/Entity.h"
#include "Headers/InputComponent.h"

void InputComponent::update(Entity& player) {

    std::vector<Message> inputs = engine->_inputs->getInputs();

    player.velocity.x =0;
    player.velocity.y =0;


    for(auto& action : inputs){
        if(action.message == "MOVE") {
            player.velocity.x = action.dir.x;
            player.velocity.y = action.dir.y;
        }
    }
}