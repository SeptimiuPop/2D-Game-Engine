#include "Headers/Includes.h"
#include "Headers/Room.h"
#include "Headers/InputComponent.h"
#include "Headers/PhysicsComponent.h"
#include "Headers/RenderComponent.h"



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



    Room::Room(): roomCount(0){
    }


    Room::~Room(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Room::setEngine(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
        initPlayer();
        generateRoom();  
        view.setSize(sf::Vector2f(320,180));
    }

    void Room::initPlayer(){
        
        InputComponent input;
        PhysicsComponent physics;
        RenderComponent renderer;
        renderer.initComponent(engine->_assets->getTexture("pl"), 16, 32);
        player = Entity(input, physics, renderer);
    }

    void Room::initMap(std::string filename){
        map.clear();
        
        int style, choice, tileX, tileY;
        
        std::ifstream config(filename);
        if(config.is_open()){
            // get the size and style of the room
            config >> width >> height;
            config >> style;
            for(int i=0; i<width; i++){
                std::vector<Tile> row;
                for(int j=0; j<height; j++){
                    
                    config >> choice;
                    Tile tile(sf::Vector2f(i*16,j*16), true);
                    tile.setTexture(engine->_assets->getTexture("tileset"));

                    tileX = choice/10*16;
                    tileY = choice%10*16 + style*4*16; 

                    tile.setTexturePos(sf::IntRect(tileX, tileY,16,16));
                    
                    //place the tile in the row map 
                    row.push_back(tile);
                }
                // place the row on the map
                map.push_back(row);
            }
        }

        config.close();
    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Room::generateRoom(){
        srand(time(0));
        int roomChoice = random()%3;
        
        switch (roomChoice)
        {
        case 0:
            initMap("../config/Rooms/Room_2.ini");
            break;
        case 1:
            initMap("../config/Rooms/Room_3.ini");
            break;
        case 2:
            initMap("../config/Rooms/Room_4.ini");
            break;
        default:
            break;
        }
        player.x = width/2  * 16;
        player.y = height/2 * 16;
    }

    void Room::update(){
        UpdateView();
    }

    void Room::draw(){
        
        engine->_window->setView(view);

        // on each tile of the map do:
        for(int i=0; i<width; i++){
            for(int j=0; j<height; j++){
                map[i][j].draw(*engine->_window);
            }
        }
        player.update(20, engine->_window);
    }

    void Room::UpdateView(){
        /* Sets the view of the window around the player */
        sf::Vector2i cursor = sf::Mouse::getPosition(*engine->_window);

        // center the mouse position
        cursor.x -= engine->_window->getSize().x/2;
        cursor.y -= engine->_window->getSize().y/2;
        
        // set the view position to be centered on the player
        // plus a small offset given by the mouse pozition
        sf::Vector2f view_bounds;
        view_bounds.x = player.x + 16 + (cursor.x)/32;
        view_bounds.y = player.y + 16 + (cursor.y)/16;

        view.setCenter(view_bounds);

    }