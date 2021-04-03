#include "Headers/Includes.h"
#include "Headers/GameMenu.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    GameMenu::GameMenu(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void GameMenu::setEngine(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
    }


    void GameMenu::InitMessage(){
        menu_message.setFont(engine->_assets->getFont("main_menu"));
        if(engine->game_state == "MAIN_MENU")
            menu_message.setString("Tale Of A Mouse");
        else
            menu_message.setString(engine->game_state);
        menu_message.setFillColor(sf::Color::Red);
        menu_message.setCharacterSize(88);
        menu_message.setPosition(600,50);
    }

    void GameMenu::InitActions(){
        

        if(!actions.empty())
            actions.clear();

        if(engine->game_state == "MAIN_MENU"){
            actions.push_back("Play");
            actions.push_back("Quit");
        }
        if(engine->game_state == "PAUSED"){

            actions.push_back("Resume");
            actions.push_back("New Game");
            actions.push_back("Main Menu");
            actions.push_back("Quit");
        }
        if(engine->game_state == "GAME_OVER"){

            actions.push_back("New Game");
            actions.push_back("Main Menu");
            actions.push_back("Quit");
        }
    }

    void GameMenu::InitButtons(){

        if(!buttons.empty())
            buttons.clear();

        sf::Vector2f pos(200,350);

        for(int i=0; i<actions.size(); i++){
            Button aux;
            buttons.push_back(aux);
            buttons[i].initButton(engine->_assets->getFont("main_menu"), actions[i], pos, 1, sf::Color::Blue, sf::Color::White);
            pos.y += 100;
        }
    }

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void GameMenu::Init(){
        InitMessage();
        InitActions();
        InitButtons();
    }

    void GameMenu::Update(){
        
        sf::Vector2i mouse = sf::Mouse::getPosition(*engine->_window);
        bool ok = false;

        for(int i=0; i<buttons.size(); i++){
            if(buttons[i].isMouseOver(mouse)){
                
                buttons[selected].setBgColor(sf::Color::Blue);
                
                selected = i;
                buttons[i].setBgColor(sf::Color::Red);
                
                if(buttons[i].getLabel() == "Quit" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    engine->_window->close();
                
                if(buttons[i].getLabel() == "Play" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    engine->game_state = "NEW_GAME";
                
                if(buttons[i].getLabel() == "Resume" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    engine->game_state = "IN_GAME";
                    
                if(buttons[i].getLabel() == "Main Menu" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    engine->game_state = "MAIN_MENU";
                    Init();
                   }
                                   
                if(buttons[i].getLabel() == "New Game" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                    engine->game_state = "NEW_GAME";
            }
            else{
                buttons[i].setBgColor(sf::Color::Blue);
            }
        }
    }


    void GameMenu::Draw(){
        engine->_window->draw(menu_message);

        for(auto& b : buttons){
            b.Draw(engine->_window);
        }        
    }
