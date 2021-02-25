#include "Game.h"
#include "input_handler.h"

    //initialization
    void Game::initWindow(){

        std::ifstream config("../config/init_window.txt");
        std::string title = "None";
        sf::VideoMode bounds(640, 480);
        int framerate = 120;

        if(config.is_open()){
            std::getline(config, title);
            
            config >> bounds.width >> bounds.height;
            // if(fullscreen)
            config >> bounds.width >> bounds.height;
            config >> framerate;
        }

        config.close();

        window->create(bounds,title, sf::Style::Fullscreen);

        if (fullscreen){
            width = 1920;
            height = 1080;
        }
        else{
            width = 640;
            height = 480;
            window->create(sf::VideoMode(width, height),title, sf::Style::Default);
        }

        // window->setKeyRepeatEnabled(false);
    }


    //constructor/destructor
    Game::Game(){
        window = new sf::RenderWindow(sf::VideoMode(640, 480),"C++ Game", sf::Style::Default);  
        
        Entity e(250,250);
        entities.push_back(e);
        entities[0].initSprite("../assets/sprite.png");

        bg_t.loadFromFile("../assets/bg.jpeg"); 
        
        bg_s.setTexture(bg_t);
        bg_s.setPosition(0,0);

        
        initWindow();
    }

    Game::~Game(){
        delete window;
    }


    //function
    void Game::UpdateSFMLEvents(){
        
        // std::cout<<handle_mouse(sfEvent, mouse);
        // std::cout<<handle_keys(sfEvent, key);

        while (window->pollEvent(sfEvent)){
    
            if (sfEvent.type == sf::Event::Closed)
                window->close();

            if(key.isKeyPressed(key.Escape)) window->close();
            if(key.isKeyPressed(key.W)) entities[0].move(0,-1);
            if(key.isKeyPressed(key.A)) entities[0].move(-1,0);
            if(key.isKeyPressed(key.S)) entities[0].move(0, 1);
            if(key.isKeyPressed(key.D)) entities[0].move(1, 0);
            if(key.isKeyPressed(key.Space)) slowed = true;
            if(mouse.isButtonPressed(mouse.Right)) draw=true;
            
            if(sfEvent.type == sf::Event::KeyReleased){
                if (sfEvent.key.code == key.Enter 
                && key.isKeyPressed(key.LAlt)){
                    fullscreen = !fullscreen;
                    initWindow();
                }
                if(sfEvent.key.code == key.W) move = false;
                if(sfEvent.key.code == key.A) move = false;
                if(sfEvent.key.code == key.S) move = false;
                if(sfEvent.key.code == key.D) move = false;
                if(sfEvent.key.code == key.Space) slowed = false;
            }
            if (sfEvent.type == sf::Event::MouseButtonReleased)
                if (sfEvent.mouseButton.button == mouse.Right)
                    draw = false;
        }
    }

    void Game::UpdateMovement(){


        // sf::Vector2i localPosition = mouse.getPosition(*window);
        // float mouse_dx = localPosition.x;
        // float mouse_dy = localPosition.y;
        
        //when spacebar pressed, reduce the speed
                

        //vars used in relative position

        // entities[0].update_on_mouse(target_x,target_y);

    }

    void Game::update(){
        UpdateSFMLEvents();
        UpdateMovement();
    }

    void Game::render(){
            
            window->clear();

            window->draw(bg_s);

            entities[0].draw(window,width,height);

            window->display();
    }

    void Game::run(){
        
        while(window->isOpen()){
            update();
            render();

        }
    }
