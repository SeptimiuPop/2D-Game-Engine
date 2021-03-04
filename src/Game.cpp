#include "Includes.h"
#include "Game.h"

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

    void Game::initEntities(){
        
        Entity bg(0,0);
        entities.push_back(bg);
        
        Entity animated(100,0);
        entities.push_back(animated);
        
        Entity player(960,540);
        entities.push_back(player);
        
        Entity tileset(100,500);
        entities.push_back(tileset);
        
        entities[0].initSprite("../assets/bg.jpeg", 1, 1920, 1080);
        entities[1].initSprite("../assets/Ground_Monk.png", 3.5, 100, 64);
        entities[2].initSprite("../assets/sprite.png",4,32,32);
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

    //constructor/destructor
    Game::Game(){
        
        initWindow();
        initEntities();

        view.setSize(sf::Vector2f(1440,810));        
    }

    Game::~Game(){
        delete window;
    }


    //function
    void Game::UpdateSFMLEvents(){
        
        handler.handle_input(window);

        while (window->pollEvent(sfEvent)){
    
            if (sfEvent.type == sf::Event::Closed)
                window->close();

            if(key.isKeyPressed(key.Escape)) window->close();
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
        sf::Vector2i cursor = mouse.getPosition(*window);
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
