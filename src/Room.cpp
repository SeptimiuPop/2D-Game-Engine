#include "Headers/Includes.h"
#include "Headers/Room.h"
#include "Headers/InputComponent.h"
#include "Headers/PhysicsComponent.h"
#include "Headers/RenderComponent.h"



    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/



    Room::Room(): roomCount(0){
        generateRoom();
    }


    Room::~Room(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/

    void Room::setEngine(std::shared_ptr<Engine> game_engine){
        engine = game_engine;
        initPlayer();
    }

    void Room::initPlayer(){
        
        InputComponent input;
        PhysicsComponent physics;
        RenderComponent renderer;
        renderer.initComponent(engine->_assets->getTexture("pl"), 16, 32);
        player = Entity(input, physics, renderer);
    }


    void Room::initMap(){
        map.clear();
        for(int i=0; i<width; i++){
            std::vector<Tile> row;
            for(int j=0; j<height; j++){
            
                Tile tile(sf::Vector2i(i*16,j*16), true);


                if(j == 0){
                    if(i==0)
                        tile.setTexturePos(sf::IntRect(0,0,16,16));
                    if(i==width-1)
                        tile.setTexturePos(sf::IntRect(48,0,16,16));
                    else
                        tile.setTexturePos(sf::IntRect((i%2+1)*16,0,16,16));
                }
                else if(j == height-1){
                    if(i==0)
                        tile.setTexturePos(sf::IntRect(0,48,16,16));
                    if(i==width-1)
                        tile.setTexturePos(sf::IntRect(48,48,16,16));
                    else
                        tile.setTexturePos(sf::IntRect((i%2+1)*16,48,16,16));
                }
                else if(i==0)
                    tile.setTexturePos(sf::IntRect(0,(j%2+1)*16,16,16));
                else if(i==width-1)
                    tile.setTexturePos(sf::IntRect(48,(j%2+1)*16,16,16));
                else
                    tile.setTexturePos(sf::IntRect(80,48,16,16));
                //place the tile in the row map 
                row.push_back(tile);
            }

            // place the row on the map
            map.push_back(row);
        }
    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


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
        
        player.update(20, engine->_window);
        
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

