#include "Headers/Includes.h"
#include "Headers/Game.h"

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game():
        engine(std::make_shared<Engine>()){
        engine->game_state="MAIN_MENU";

        room.setEngine(engine);        
        menu.setEngine(engine);        
        menu.Init();

        initWindow();
        initBgMusic();
    }

    Game::~Game(){}



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    //initialization
    void Game::initWindow(){
        /*
        std::ifstream config("../config/init_window.txt");
        std::string title = "None";
        sf::VideoMode bounds(1920, 1080);
        int framerate = 120;

        if(config.is_open()){
            std::getline(config, title);
            
            config >> bounds.width >> bounds.height;
            config >> bounds.width >> bounds.height;
            config >> framerate;
        }

        config.close();
        */
        fullscreen = false;
        setVideoMode();
    }

    void Game::initBgMusic(){
        if (!music.openFromFile("../assets/Audio/Timberbrook.wav"))
            throw("Could not load Timberbrook.wav");
        
        music.play();
        music.setVolume(5.f);
        music.setLoop(true);
        music.setPitch(1.f);
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
            std::cout<<dt<<"\n";
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
            room.draw();
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
            room.generateRoom();
            engine->game_state = "IN_GAME";
        }
        else if(engine->game_state == "IN_GAME"){
            room.update();
        }
        else{
            menu.Update();
        }
    }

    // SHOULD CHANGE TO INCLUDE ONLY WINDOW OPTIONS AND 
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
                }
                else if(engine->game_state == "PAUSED")
                    engine->game_state = "IN_GAME";
            }
            if(action.message == "FULLSCREEN") setVideoMode();   
        }
    }



