//
// Created by Master Móviles on 06/04/2017.
//
#pragma  once

#include <string>
#include <unordered_map>
#include <audio/include/SimpleAudioEngine.h>
#include <vector>

namespace Entities {


    class Sound {
    private:
        std::vector<std::string> soundVector{"open_door.mp3","jump.wav"};
        std::unordered_map<std::string, int> mapSounds;
        std::unordered_map<std::string, int> mapBackground;
        static Sound* instance;
        CocosDenshion::SimpleAudioEngine* audio;
        inline Sound();

    public:
        static Sound *getInstance();
        CocosDenshion::SimpleAudioEngine* getAudio();
        void clearSounds();
        void stopSound(std::string sound);
        void stopBackground(std::string sound);
        void playSound(std::string sound);
        void playBackground(std::string sound);
        void pauseBackground();
        void resumeBackground();
    };
}
