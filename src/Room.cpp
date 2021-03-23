#include "Headers/Includes.h"
#include "Headers/Room.h"


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    Room::Room(): roomCount(0){
        generateRoom();
    }

    Room::~Room(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Room::initMap(){
        map.clear();
        for(int i=0; i<width; i++){
            std::vector<Tile> row;
            for(int j=0; j<height; j++){
            
                Tile tile(sf::Vector2i(i*16,j*16), true);
                // if we are at the edge of the map
                if(i==0||i==width-1||j==0||j==height-1)
                    tile.setTexturePos(sf::IntRect(0,16,16,16));
                // if we are at the interior of the map
                else{
                    tile.setTexturePos(sf::IntRect(32,48,16,16));
                }
                
                //place the tile in the row map 
                row.push_back(tile);
            }

            // place the row on the map
            map.push_back(row);
        }
    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void Room::setEngine(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
    }

    void Room::generateRoom(){
        if(roomCount == 0){
            height = 15;
            width = 20;
            roomCount ++;
        }else if(roomCount > 5){
            height = 15;
            width = 20;
        }else{
            srand(time(0));
            width = random()%15 + 15;
            height = random()%15 + 15;
            roomCount ++;
        }
        initMap();
    }

    void Room::draw(){
        
        // some mock-up sprite to draw on
        sf::Sprite sprite;
        sprite.setTexture(engine->_assets->getTexture("tileset"));
        sprite.setScale(sf::Vector2f(1,1));

        // on each tile of the map do:
        for(int i=0; i<width; i++)
            for(int j=0; j<height; j++){

                // get the alocated texture, set pos and draw
                sprite.setTextureRect(map[i][j].getTexturePos());
                sprite.setPosition(16*i,16*j);
                engine->_window->draw(sprite);
            }
    }

