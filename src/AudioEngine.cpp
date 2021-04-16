#include "Headers/Includes.h"
#include "Headers/AudioEngine.h"

    AudioEngine::~AudioEngine(){
        for(int i =0; i<audio_channels.size(); i++){
            Stop(i);
            delete audio_channels[i];
            audio_channels[i] = nullptr;
        }
        audio_channels.clear();
    }


    bool AudioEngine::checkValidID(int channelID){
        if(channelID >= 0 && channelID < audio_channels.size())
            return true;
        return false;
    }

    void AudioEngine::Play(int channelID){
        if(checkValidID(channelID))
            audio_channels[channelID]->play();
    }

    void AudioEngine::Pause(int channelID){
        if(checkValidID(channelID))
            audio_channels[channelID]->pause();
    }
    
    void AudioEngine::Stop(int channelID){
        if(checkValidID(channelID))
            audio_channels[channelID]->stop();
    }
    
    void AudioEngine::AdjustChannel(int channelID, float volume, float pitch, bool looping){
        if(checkValidID(channelID)){
            audio_channels[channelID]->setVolume(volume);
            audio_channels[channelID]->setPitch(pitch);
            audio_channels[channelID]->setLoop(looping);
        }
    }

    void AudioEngine::LoadChannel(std::string filename){
        audio_channels.push_back(new sf::Music);
        int ID = audio_channels.size() - 1;
        if (!audio_channels[ID]->openFromFile(filename))
            throw("Could not load audio track");
        
        AdjustChannel(ID, 100.f, 1.f, false);
    }
    