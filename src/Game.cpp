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
        view.setSize(sf::Vector2f(320,180));
    }

    void Game::initBgMusic(){
        if (!music.openFromFile("../assets/Audio/Timberbrook.wav"))
            throw("Could not load Timberbrook.wav");
        
        music.play();
        music.setVolume(30.f);
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
    }



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::Run(){
        while(engine->_window->isOpen()){ 
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
        }
        else{
            menu.Draw();
        }

        engine->_window->display();
    }




    void Game::Update(){   

        engine->_inputs->handle_inputs();
        
        if(engine->game_state == "IN_GAME"){
            UpdatePlayerEvents();
        }
        else{
            std::string state = engine->game_state;
            menu.Update();

            // if the game changed from some menu option to MAIN_MENU
            if(engine->game_state != state && engine->game_state == "MAIN_MENU")
                menu.Init();
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
                engine->game_state = "PAUSED";
                menu.Init();
            }
            if(action.message == "FULLSCREEN") setVideoMode();            
        }
    }



