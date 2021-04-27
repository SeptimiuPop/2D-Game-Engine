#pragma once 

class ResourceManager{
    
    private:
        std::map<std::string, sf::Texture> textures;
        std::map<std::string, sf::Font> fonts;
        std::map<std::string, sf::SoundBuffer> sound;
        std::map<std::string, std::string> music;

        void initAssets();


    public:
        ResourceManager();
        ~ResourceManager();

        void loadTexture(std::string name, std::string fileName);
        sf::Texture &getTexture(std::string name);

        void loadFont(std::string name, std::string fileName);
        sf::Font &getFont(std::string name);

        void loadSound(std::string name, std::string fileName);
        sf::SoundBuffer &getSound(std::string name);

        void loadMusic(std::string name, std::string fileName);
        std::string &getMusic(std::string name);
};
