#include "Headers/Includes.h"
#include "Headers/GameState.h"
#include "Headers/AIComponent.h"
#include "Headers/InputComponent.h"
#include "Headers/PhysicsComponent.h"
#include "Headers/RenderComponent.h"



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



    GameState::GameState(): roomCount(0){
    }


    GameState::~GameState(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void GameState::setEngine(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
        initPlayer();
        view.setSize(sf::Vector2f(320,180));
    }

    void GameState::initPlayer(){
        
        InputComponent input(engine);
        PhysicsComponent physics(&map);
        RenderComponent renderer;
        renderer.initComponent(engine->_assets->getTexture("player"), 16, 32);
        player = Entity(input, physics, renderer);
    }

    void GameState::initMap(std::string filename){

        std::ifstream config(filename);
        std::string label;
        int tileset_size, choice, tileX, tileY;
        char cma;

        map.clear();

        if(config.is_open()){
            // get the size and style of the room
            config >> width >> height;
            config >> tileset_size;

            map.resize(height);
            for(int i=0; i<height; i++){
                map[i].resize(width);
                for(int j=0; j<width; j++){
                    Tile tile(sf::Vector2f(j*16,i*16));
                    tile.setTexture(engine->_assets->getTexture("tileset"));
                    map[i][j] = tile;       
                }
            }


            while(label != "col"){
                config>>label;

                for(int i=0; i<height; i++){
                    for(int j=0; j<width; j++){
                
                        config >> choice;
                        config >> cma;

                        if(label == "layer"){
                            choice --;
                            tileX = choice%tileset_size*16; 
                            tileY = choice/tileset_size*16;
                            map[i][j].setTexturePos(sf::IntRect(tileX, tileY,16,16));   
                        }
                        else     
                            map[i][j].setBlocking(choice);       
                    }
                }

            }
        }
        config.close();
    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void GameState::generateRoom(){
        
        switch (roomCount)
        {
        case 0:
            initMap("../config/Rooms/Room_2.ini");
            break;
        case 1:
            initMap("../config/Rooms/Room_1.ini");
            break;
        case 2:
            initMap("../config/Rooms/Room_3.ini");
            break;
        case 3:
            initMap("../config/Rooms/Room_4.ini");
            break;
        case 4:
            initMap("../config/Rooms/Room_5.ini");
            break;
        default:
            break;
        }

        player.x = width/2  * 16;
        player.y = height/2 * 16;

        roomCount = (roomCount + 1) % 5;
    }

    void GameState::Update(const float dt){
        UpdateView();

    }

    void GameState::Draw(const float dt){
        engine->_window->setView(view);

        // on each tile of the map do:
        for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                map[i][j].draw(*engine->_window);
            }
        }
        player.update(dt, engine->_window);
    }

    void GameState::UpdateView(){
        /* Sets the view of the window around the player */
        sf::Vector2i cursor = sf::Mouse::getPosition(*engine->_window);

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