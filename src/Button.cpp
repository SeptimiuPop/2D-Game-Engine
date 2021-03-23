#include "Headers/Includes.h"
#include "Headers/Button.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Button::Button(){
        sf::Vector2f size(200,50);
        button.setSize(size);
    }

    void Button::initButton(const sf::Font& font, std::string text, sf::Vector2f pos, float scale, sf::Color bgColor, sf::Color textColor){
        
        sf::Vector2f size(200,50);
        size.x *= scale;
        size.y *= scale;

        button.setPosition(pos.x, pos.y);
        button.setSize(size);
        button.setFillColor(bgColor);

        // init button properties
        label.setFont(font);
        label.setString(text);
        label.setFillColor(textColor);
        label.setPosition(pos.x+size.y/4, pos.y);
    }

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/




    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Button::setBgColor(sf::Color color){
        button.setFillColor(color);
    }

    void Button::setTextColor(sf::Color color){
        label.setFillColor(color);
    }

    std::string Button::getLabel(){
        return label.getString();
    }

    bool Button::isMouseOver(sf::Vector2i mouse){
        sf::FloatRect bounds = button.getGlobalBounds();
        if(mouse.x > bounds.left &&
            mouse.y > bounds.top &&
            mouse.x < bounds.left + bounds.width &&
            mouse.y < bounds.top  + bounds.height)
            {
                return true;
            }
        return false;
    }


    void Button::Draw(std::shared_ptr<sf::RenderWindow> window){
        window->draw(button);
        window->draw(label);
    }


