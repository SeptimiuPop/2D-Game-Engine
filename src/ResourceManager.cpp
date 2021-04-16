#include "Headers/Includes.h"
#include "Headers/ResourceManager.h"

    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- CONSTRUCTOR / DESTRUCTOR -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/
    ResourceManager::ResourceManager(){
        initAssets();
    }
    ResourceManager::~ResourceManager(){}


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PRIVATE FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    void ResourceManager::initAssets(){
        // textures
        loadTexture("mo","../assets/Textures/Ground_Monk.png");
        loadTexture("pl","../assets/Textures/Sprites.png");
        loadTexture("ui","../assets/Textures/ui_health.png");
        loadTexture("tileset","../assets/Textures/Tileset.png");

        // fonts
        loadFont("main_menu", "../assets/Fonts/alphbeta.ttf");

        // sound
        loadSound("walk_stone","../assets/Audio/player/boot_stone_01.wav");
        loadSound("walk_carpet","../assets/Audio/player/boot_carpet_01.wav");

        // music 
        loadMusic("main_menu","../assets/Audio/2019-06-14_-_Warm_Light_-_David_Fesliyan.wav");
        loadMusic("in_game","../assets/Audio/Timberbrook.wav");
    }


    /*-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- PUBLIC  FUNCTIONS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=*/


    /* LOAD AND GET TEXTURE*/
    void ResourceManager::loadTexture(std::string name, std::string fileName){
        sf::Texture tex;
        if(tex.loadFromFile(fileName)){
            textures[name] = tex;
        }
    }
    sf::Texture &ResourceManager::getTexture(std::string name){
        return textures.at(name);
    }


    /* LOAD AND GET FONT*/
    void ResourceManager::loadFont(std::string name, std::string fileName){
        sf::Font font;
        if(font.loadFromFile(fileName)){
            fonts[name] = font;
        }
    }
    sf::Font &ResourceManager::getFont(std::string name){
        return fonts.at(name);
    }
    

    /* LOAD AND GET SOUND*/
    void ResourceManager::loadSound(std::string name, std::string fileName){
        sf::SoundBuffer buffer;
        if(buffer.loadFromFile(fileName)){
            sound[name] = buffer;
        }
    }
    sf::SoundBuffer &ResourceManager::getSound(std::string name){
        return sound.at(name);
    }


    /* LOAD AND GET MUSIC*/
    void ResourceManager::loadMusic(std::string name, std::string fileName){
        music[name] = fileName;
    }
    std::string &ResourceManager::getMusic(std::string name){
        return music.at(name);
    }