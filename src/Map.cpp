#include "Headers/Includes.h"
#include "Headers/Map.h"


    Map::Map(): roomCount(0){
        generateRoom();
    }

    Map::~Map(){}


    void Map::initMap(){
        map.clear();
        for(int i=0; i<width; i++){
            std::vector<Tile> row;
            for(int j=0; j<height; j++){
            
                Tile tile(sf::Vector2i(i*16,j*16), true);
                // if we are at the edge of the map
                if(j==1 && i!=0 && i != width-1)
                    tile.setTexturePos(sf::IntRect(0,32,16,16));
                else if(j==0 && i!=0 && i != width-1){
                    int random_tile = rand()%15;
                    if(random_tile == 0)
                        tile.setTexturePos(sf::IntRect(192,64,16,16));
                    if(random_tile == 1)
                        tile.setTexturePos(sf::IntRect(64,16,16,16));
                    if(random_tile == 2)
                        tile.setTexturePos(sf::IntRect(64,32,16,16));
                    if(random_tile == 3)
                        tile.setTexturePos(sf::IntRect(64,48,16,16));
                    if(random_tile > 3)
                        tile.setTexturePos(sf::IntRect(0,16,16,16));

                }else if(i==0||i==width-1||j==height-1)
                    tile.setTexturePos(sf::IntRect(0,16,16,16));
                // if we are at the interior of the map
                else{
                    int random_tile = rand()%15;
                    if(random_tile < 8)
                        tile.setTexturePos(sf::IntRect(16,96,16,16));
                    if(random_tile >= 8)
                        tile.setTexturePos(sf::IntRect(32,48,16,16));
                }
                
                //place the tile in the row map 
                row.push_back(tile);
            }

            // place the row on the map
            map.push_back(row);
        }
    }

    void Map::generateRoom(){
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

    void Map::draw(sf::RenderWindow* window, sf::Texture& tx){
        
        // some mock-up sprite to draw on
        sf::Sprite sprite;
        sprite.setTexture(tx);
        sprite.setScale(sf::Vector2f(3,3));

        // on each tile of the map do:
        for(int i=0; i<width; i++)
            for(int j=0; j<height; j++){

                // get the alocated texture, set pos and draw
                sprite.setTextureRect(map[i][j].getTexturePos());
                sprite.setPosition(3*16*i,3*16*j);
                window->draw(sprite);
            }
    }

