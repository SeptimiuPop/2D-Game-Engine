#include "Headers/Includes.h"
#include "Headers/Game.h"

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game(){
        engine = std::make_shared<Engine>();
        initWindow();
        initBgMusic();
        initEntities();
        initUIElements();
    }

    Game::~Game(){
        delete window;
    }



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

        width = 1920;
        height = 1080;
        window = new sf::RenderWindow(sf::VideoMode(width,height), "Tale-of-a-Mouse", sf::Style::Fullscreen);  
        
        window->setKeyRepeatEnabled(false);
        window->setVerticalSyncEnabled(true);
        view.setSize(sf::Vector2f(1440,810));
    }

    void Game::initBgMusic(){
        if (!music.openFromFile("../assets/Audio/Timberbrook.wav"))
            std::cout<<"\n\nSo silent..\n\n";

        music.play();
        music.setVolume(10.f);
        music.setLoop(true);
        music.setPitch(1.f);
    }

    void Game::initEntities(){
        
        for(int i=0; i<3; i++){
            Entity en(i*200,0);
            entities.push_back(en);
        }

        // entities[0].initSprite(engine->_assets->getTexture("bg"), 2, 1920, 1088);
        entities[1].initSprite(engine->_assets->getTexture("mo"), 3.5, 100, 64);
        entities[2].initSprite(engine->_assets->getTexture("pl"),3.5,32,32);
        
        // sound
        entities[2].initSound(engine->_assets->getSound("walk_stone"), 60.f, 1.f);
    }

    void Game::initUIElements(){
        
        Entity ui_health(20,20);
        ui.push_back(ui_health);
        
        ui[0].initSprite(engine->_assets->getTexture("ui"),0.2,900,300);
    }

    void Game::changeVideoMode(){
        fullscreen = !fullscreen;
        if (fullscreen){
            width = 1920;
            height = 1080;
            window->create(sf::VideoMode(width, height),"Tale-of-a-Mouse", sf::Style::Fullscreen);
        }
        else{
            width = 960;
            height = 540;
            window->create(sf::VideoMode(width, height),"Tale-of-a-Mouse", sf::Style::Default);
        }
    }



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Game::UpdatePlayerEvents(){

        /* Calls the input handler to get user input as vector of messages 
        * and iterates the list to take action */

        bool slowed = false;
        bool draw = false;
        bool dash = false;
        sf::Vector2i move_direction;

        std::vector<Message> inputs = engine->_inputs->handle_input(window);

        for(auto& action : inputs){
            // window actions
            if(action.message == "CLOSE") window->close();
            if(action.message == "FULLSCREEN") changeVideoMode();
            
            // mock animation actions
            if(action.message == "DRAW") draw = action.check;
            if(action.message == "NEXT") entities[1].next_anim();
            if(action.message == "PREV") entities[1].prev_anim();
            if(action.message == "RESET") entities[1].reset_anim();

            if(action.message == "NR") map.generateRoom();
            
            // movement actions
            if(action.message == "DASH") dash = action.check;
            if(action.message == "SLOW") slowed = action.check;
            if(action.message == "MOVE") move_direction = action.dir;
        }

        entities[1].animate(dt, draw);
        entities[2].update(dt, move_direction, slowed, dash, window);

    }

    void Game::UpdateView(){
        /* Sets the view of the window around the player */
        sf::Vector2i cursor = sf::Mouse::getPosition(*window);
        sf::Vector2f player = entities[2].getPozition();
        sf::Vector2f view_bounds = view.getSize();

        // center the mouse position
        cursor.x -= width/2;
        cursor.y -= height/2;
        
        // set the view position to be centered on the player
        // plus a small offset given by the mouse pozition
        view_bounds.x = player.x + (cursor.x)/8;
        view_bounds.y = player.y + (cursor.y)/4;

        view.setCenter(view_bounds);
    }

    void Game::Update(){   
        UpdatePlayerEvents();
        UpdateView();
    }

    void Game::Render(){  

        window->clear();
        
        // draw game elements in view
        window->setView(view);
        map.draw(window, engine->_assets->getTexture("tileset"));
        for(auto& en:entities) 
            en.draw(window,1920,1080);
        

        // draw UI elements
        window->setView(window->getDefaultView());
        for(auto& en:ui) 
            en.draw(window,1920,1080);
        

        window->display();
    }

    void Game::Run(){
        while(window->isOpen()){ 
            dt = dtClock.getElapsedTime().asSeconds();
            dtClock.restart();

            if(window->hasFocus()){
                Update();
                Render();
            }
        }
    }
