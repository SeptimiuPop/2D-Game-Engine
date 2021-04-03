#pragma once

class Button{
    private:
        sf::Text label;
        sf::RectangleShape button;




    public:
        Button();

        void initButton(const sf::Font& font, std::string text, sf::Vector2f pos, float scale, sf::Color bgColor, sf::Color textColor);

        void setBgColor(sf::Color color);
        void setTextColor(sf::Color color);
        sf::String getLabel();

        bool isMouseOver(sf::Vector2i mouse);
        void Draw(std::shared_ptr<sf::RenderWindow> window);

};  
