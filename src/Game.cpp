#include "Headers/Includes.h"
#include "Headers/Game.h"

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game():
        engine(std::make_shared<Engine>()){
        engine->game_state="MAIN_MENU";
        
        menu = GameMenu(engine);
        menu.Init();

        initWindow();
        initBgMusic();
        initEntities();
        initUIElements();
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
            std::cout<<"\n\nSo silent..\n\n";

        music.play();
        music.setVolume(100.f);
        music.setLoop(true);
        music.setPitch(1.f);
    }

    void Game::initEntities(){
        
        room.setEngine(engine);
        
        for(int i=0; i<3; i++){
            Entity en(i*200,0);
            entities.push_back(en);
        }

        // entities[0].initSprite(engine->_assets->getTexture("bg"), 2, 1920, 1088);
        entities[1].initSprite(engine->_assets->getTexture("mo"), 1, 100, 64);
        entities[2].initSprite(engine->_assets->getTexture("pl"),1,32,32);
        
        // sound
        entities[2].initSound(engine->_assets->getSound("walk_stone"), 60.f, 1.f);
    }

    void Game::initUIElements(){
        
        Entity ui_health(20,20);
        ui.push_back(ui_health);
        
        ui[0].initSprite(engine->_assets->getTexture("ui"),0.2,900,300);
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
            // draw game elements in view
            engine->_window->setView(view);
            room.draw();
            for(auto& en:entities) 
                en.draw(engine->_window);
            

            // draw UI elements
            engine->_window->setView(engine->_window->getDefaultView());
            for(auto& en:ui) 
                en.draw(engine->_window);
        }
        else{
            menu.Draw();
        }

        engine->_window->display();
    }




    void Game::Update(){   
        if(engine->game_state == "IN_GAME"){
            UpdatePlayerEvents();
            UpdateView();
        }
        else{
            std::string state = engine->game_state;
            menu.Update();
            if(engine->game_state != state && engine->game_state == "MAIN_MENU")
                menu.Init();
        }
    }


    void Game::UpdatePlayerEvents(){

        /* Calls the input handler to get user input as vector of messages 
        * and iterates the list to take action */

        bool slowed = false;
        bool draw = false;
        bool dash = false;
        sf::Vector2i move_direction;

        std::vector<Message> inputs = engine->_inputs->handle_input();

        for(auto& action : inputs){
            // window actions
            if(action.message == "CLOSE") {
                engine->game_state = "PAUSED";
                menu.Init();
            }
            if(action.message == "FULLSCREEN") setVideoMode();
            
            // mock animation actions
            if(action.message == "DRAW") draw = action.check;
            if(action.message == "NEXT") entities[1].next_anim();
            if(action.message == "PREV") entities[1].prev_anim();
            if(action.message == "RESET") entities[1].reset_anim();

            if(action.message == "NR") room.generateRoom();
            
            // movement actions
            if(action.message == "DASH") dash = action.check;
            if(action.message == "SLOW") slowed = action.check;
            if(action.message == "MOVE") move_direction = action.dir;
        }

        entities[1].animate(dt, draw);
        entities[2].update(dt, move_direction, slowed, dash, engine->_window);

    }

    void Game::UpdateView(){
        /* Sets the view of the window around the player */
        sf::Vector2i cursor = sf::Mouse::getPosition(*engine->_window);
        sf::Vector2f player = entities[2].getPozition();

        // center the mouse position
        cursor.x -= engine->_window->getSize().x/2;
        cursor.y -= engine->_window->getSize().y/2;
        
        // set the view position to be centered on the player
        // plus a small offset given by the mouse pozition
        sf::Vector2f view_bounds;
        view_bounds.x = player.x + (cursor.x)/32;
        view_bounds.y = player.y + (cursor.y)/16;

        view.setCenter(view_bounds);
    }


