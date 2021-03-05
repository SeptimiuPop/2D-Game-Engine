#include "Includes.h"
#include "Game.h"

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    Game::Game(){
        
        initWindow();
        initBgMusic();
        initEntities();

        view.setSize(sf::Vector2f(1440,810));     
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
        
        // window->setKeyRepeatEnabled(false);
    }


    void Game::initBgMusic(){
        if (!music.openFromFile("../sound/Timberbrook.wav"))
            std::cout<<"\n\nSo silent..\n\n";

        music.play();
        music.setVolume(50.f);
        music.setLoop(true);
        music.setPitch(1.f);
    }


    void Game::initEntities(){
        
        Entity bg(0,0);
        entities.push_back(bg);
        
        Entity animated(100,0);
        entities.push_back(animated);
        
        Entity player(200,200);
        entities.push_back(player);
        
        Entity tileset(100,500);
        entities.push_back(tileset);
        
        entities[0].initSprite("../assets/bg.jpeg", 1, 1920, 1080);
        entities[1].initSprite("../assets/Ground_Monk.png", 3.5, 100, 64);
        entities[2].initSprite("../assets/sprite.png",4,32,32);
        entities[2].initSound();
        // entities[1].initSprite("../assets/Tileset.png",4,16,16);
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




    void Game::UpdateSFMLEvents(){

        /* Calls the input handler to get user input as vector of messages 
        * and iterates the list to take action */

        bool slowed = false;
        bool animate = false;
        std::vector<Message> inputs = handler.handle_input(window);

        for(auto& action : inputs){
            if(action.message == "CLOSE") window->close();
            if(action.message == "FULLSCREEN") changeVideoMode();
            if(action.message == "SLOW") slowed = action.check;
            if(action.message == "DRAW") entities[1].animate(dt);;
            if(action.message == "NEXT") entities[1].next_anim();
            if(action.message == "PREV") entities[1].prev_anim();
            if(action.message == "RESET") entities[1].reset_anim();
            if(action.message == "MOVE"){
                if(action.dir.x != 0 || action.dir.y != 0){
                    entities[2].move(action.dir.x, action.dir.y, slowed, dt);
                    animate = true;
                }
            }
        }
        sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
        sf::Vector2i screen_center(width/2, height/2);

        entities[2].update_on_mouse(screen_center, localPosition);
        entities[2].updateAnimation(dt, animate);
        entities[2].play_sound(dt, animate);
    }


    void Game::UpdateView(){
        /**/
        sf::Vector2i cursor = sf::Mouse::getPosition(*window);
        sf::Vector2f player = entities[2].getPozition();
        sf::Vector2f view_bounds = view.getSize();

        // center the mouse position
        cursor.x -= width/2;
        cursor.y -= height/2;
        
        // set the view position to be centered on the player
        // plus a small offset given by the mouse pozition
        view_bounds.x = player.x + (cursor.x)/8;
        view_bounds.y = player.y + (cursor.y)/8;

        view.setCenter(view_bounds);
    }


    void Game::update(){
        if(window->hasFocus()){
            UpdateSFMLEvents();
            UpdateView();
        }

        dt = dtClock.getElapsedTime().asSeconds();
        dtClock.restart(); 
    }


    void Game::render(){  

        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Red);
        rect.setSize(sf::Vector2f(150.f,25.f));
        rect.setPosition(20,20);

        // draw game elements in view
        window->setView(view);

        window->clear();

        for(auto& en : entities) 
            en.draw(window,1920,1080);

        // draw UI elements
        window->setView(window->getDefaultView());
        window->draw(rect);

        window->display();
    }

    void Game::run(){
        
        while(window->isOpen()){
            update();
            render();

        }
    }
