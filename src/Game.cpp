#include "Game.h"
#include "input_handler.h"

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

    void Game::initKeys(){

        // Open config file for the supported keys
        std::ifstream config("../config/supported_keys.ini");
        if(config.is_open()){
            std::string key;
            int value;

            // Assign key-value pair for the supported keys
            while(config >> key >> value)
                supportedKeys[key] = value;
        }
        config.close();
        
        // Open config file for keybinds
        config.open("../config/key_binds.ini");
        if(config.is_open()){
            std::string key;
            std::string value;

            // Assign an action to some supported key
            while(config >> key >> value)
                keyBinds[key] = supportedKeys.at(value);
        }
        config.close();
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


    //constructor/destructor
    Game::Game(){
        
        initWindow();
        initKeys();

        view.setSize(sf::Vector2f(960,540));

        Entity bg(0,0);
        entities.push_back(bg);
        
        Entity animated(100,0);
        entities.push_back(animated);
        
        Entity player(0,0);
        entities.push_back(player);
        
        Entity animated2(100,0);
        entities.push_back(animated2);
        
        entities[0].initSprite("../assets/bg.jpeg", 1, 1920, 1080);
        entities[1].initSprite("../assets/Ground_Monk.png", 3.5, 100, 64);
        entities[2].initSprite("../assets/sprite.png",4,32,32);
        
    }

    Game::~Game(){
        delete window;
    }


    //function
    void Game::UpdateSFMLEvents(){
        
        // std::cout<<handle_keys(sfEvent, key);

        while (window->pollEvent(sfEvent)){
    
            if (sfEvent.type == sf::Event::Closed)
                window->close();

            if(key.isKeyPressed(sf::Keyboard::Key(keyBinds.at("CLOSE")))) window->close();
            if(key.isKeyPressed(key.W)) {move = true; dir[0]=1;}
            if(key.isKeyPressed(key.A)) {move = true; dir[1]=1;}
            if(key.isKeyPressed(key.S)) {move = true; dir[2]=1;}
            if(key.isKeyPressed(key.D)) {move = true; dir[3]=1;}
            if(key.isKeyPressed(key.Space)) slowed = true;
            if(mouse.isButtonPressed(mouse.Right)) draw=true;

            if(sfEvent.type == sf::Event::KeyReleased){
                if (sfEvent.key.code == key.Enter 
                && key.isKeyPressed(key.LAlt)) changeVideoMode();
                if(sfEvent.key.code == key.W) {move = false; dir[0] = 0;}
                if(sfEvent.key.code == key.A) {move = false; dir[1] = 0;}
                if(sfEvent.key.code == key.S) {move = false; dir[2] = 0;}
                if(sfEvent.key.code == key.D) {move = false; dir[3] = 0;}
            
                if(sfEvent.key.code == key.E) entities[1].next_anim();
                if(sfEvent.key.code == key.Q) entities[1].prev_anim();
                if(sfEvent.key.code == key.R) entities[1].reset_anim();

                if(sfEvent.key.code == key.Space) slowed = false;
            }
            if (sfEvent.type == sf::Event::MouseButtonReleased)
                if (sfEvent.mouseButton.button == mouse.Right)
                    draw = false;
        }
    }

    void Game::UpdateMovement(){


        sf::Vector2i localPosition = mouse.getPosition(*window);
        sf::Vector2i screen_center(width/2, height/2);

        bool ok = false;
        for(int d: dir)
            if(d == 1)
                ok = true;
        move = ok;

        if(move){
            if(dir[0] == 1) entities[2].move(0,-1, slowed, dt);
            if(dir[1] == 1) entities[2].move(-1,0, slowed, dt);
            if(dir[3] == 1) entities[2].move(1, 0, slowed, dt);
            if(dir[2] == 1) entities[2].move(0, 1, slowed, dt);
        }
        
        entities[2].update_on_mouse(screen_center, localPosition);
        entities[2].updateAnimation(dt, move);

        if(draw){
            entities[1].animate(dt);
        }


    }

    void Game::UpdateView(){
        sf::Vector2f player = entities[2].getPozition();
        sf::Vector2f view_bounds = view.getSize();
        // the view should fit the game world (never going outside of it)
        // the view should then 
        view_bounds.x /=2;
        view_bounds.y /=2;

        // check if the view is within the game bounds
        if(player.x<view_bounds.x) player.x = view_bounds.x;
        if(player.x>width-view_bounds.x) player.x = width-view_bounds.x;
        if(player.y<view_bounds.y) player.y = view_bounds.y;
        if(player.y>height-view_bounds.y) player.y = height-view_bounds.y;
        view.setCenter(player);
    }

    void Game::update(){
        UpdateSFMLEvents();
        UpdateMovement();
        UpdateView();

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
            en.draw(window,width,height);

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
