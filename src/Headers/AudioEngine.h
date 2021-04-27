#pragma once

class AudioEngine{
    
    private: 
        std::vector<sf::Music *> audio_channels;
        // sf::Music music;

        bool checkValidID(int channelID);

    public:
        ~AudioEngine();

        void Play(int channelID);
        void Pause(int channelID);
        void Stop(int channelID);
        void AdjustChannel(int channelID, float volume, float pitch, bool looping);
        void LoadChannel(std::string filename);
};
