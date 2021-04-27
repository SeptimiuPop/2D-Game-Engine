#include "Headers/Includes.h"
#include "Headers/MenuState.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    MenuState::MenuState(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void MenuState::setEngine(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
    }


    void MenuState::InitMessage(){
        menu_message.setFont(engine->_assets->getFont("main_menu"));
        if(engine->game_state == "MAIN_MENU")
            menu_message.setString("Tale Of A Mouse");
        else
            menu_message.setString(engine->game_state);
        menu_message.setFillColor(sf::Color::Red);
        menu_message.setCharacterSize(88);
        menu_message.setPosition(600,50);
    }

    void MenuState::InitActions(){
        

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

    void MenuState::InitButtons(){

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

    void MenuState::Init(){
        InitMessage();
        InitActions();
        InitButtons();
    }

    void MenuState::Update(){
        
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
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    engine->game_state = "NEW_GAME";
                    engine->_audio->Pause(0);
                    engine->_audio->Stop(1);
                    engine->_audio->Play(1);
                   }
                
                if(buttons[i].getLabel() == "Resume" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    engine->game_state = "IN_GAME";
                    engine->_audio->Play(1);
                   }
                    
                if(buttons[i].getLabel() == "Main Menu" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    engine->game_state = "MAIN_MENU";
                    engine->_audio->Stop(0);
                    engine->_audio->Stop(1);
                    engine->_audio->Play(0);
                    Init();
                   }
                                   
                if(buttons[i].getLabel() == "New Game" &&
                   sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                    engine->game_state = "NEW_GAME";
                    engine->_audio->Stop(1);
                    engine->_audio->Play(1);
                   }
            }
            else{
                buttons[i].setBgColor(sf::Color::Blue);
            }
        }
    }


    void MenuState::Draw(){
        engine->_window->draw(menu_message);

        for(auto& b : buttons){
            b.Draw(engine->_window);
        }        
    }
