#include "Headers/Includes.h"
#include "Headers/Game.h"

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game():
        engine(std::make_shared<Engine>()){
        engine->game_state="MAIN_MENU";

        scene.setEngine(engine);        
        menu.setEngine(engine);        
        menu.Init();

        initWindow();
        initBgMusic();
    }

    Game::~Game(){}



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    //initialization
    void Game::initWindow(){
        fullscreen = false;
        setVideoMode();
    }

    void Game::initBgMusic(){
        // menu music
        std::string filename = engine->_assets->getMusic("main_menu");
        engine->_audio->LoadChannel(filename);
        // game music 
        filename = engine->_assets->getMusic("in_game");
        engine->_audio->LoadChannel(filename);

        engine->_audio->Play(0);
    }

    void Game::setVideoMode(){
        fullscreen = !fullscreen;
        if (fullscreen){
            engine->_window->create(sf::VideoMode(1920, 1080),"Tale-of-a-Mouse", sf::Style::Fullscreen);
        }
        else{
            engine->_window->create(sf::VideoMode(960, 540),"Tale-of-a-Mouse", sf::Style::Default);
        }
        engine->_window->setVerticalSyncEnabled(true);
    }



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while(engine->_window->isOpen()){ 
            //std::cout<<dt<<"\n";
            dt = dtClock.getElapsedTime().asSeconds();
            dtClock.restart();


            if(engine->_window->hasFocus()){
                Update();
                Render();
            }
        }
    }


    void Game::Render(){  
        engine->_window->clear();

        if(engine->game_state == "IN_GAME"){
            scene.Draw(dt);
            engine->_window->setView(engine->_window->getDefaultView());
        }
        else{
            menu.Draw();
        }

        engine->_window->display();
    }




    void Game::Update(){   

        engine->_inputs->handle_inputs();
        UpdatePlayerEvents();
        
        if(engine->game_state == "NEW_GAME"){
            scene.generateRoom();
            engine->game_state = "IN_GAME";
        }
        else if(engine->game_state == "IN_GAME"){
            scene.Update(dt);
        }
        else{
            menu.Update();
        }
    }

    void Game::UpdatePlayerEvents(){

        /* Calls the input handler to get user input as vector of messages 
        * and iterates the list to take action */

        std::vector<Message> inputs = engine->_inputs->getInputs();

        for(auto& action : inputs){
            // window actions
            if(action.message == "CLOSE") {
                if(engine->game_state == "IN_GAME"){

                    engine->game_state = "PAUSED";
                    menu.Init();
                    engine->_audio->Pause(1);
                }
                else if(engine->game_state == "PAUSED"){
                    engine->game_state = "IN_GAME";
                    engine->_audio->Play(1);
                }
            }
            if(action.message == "FULLSCREEN") setVideoMode();   
        }
    }



