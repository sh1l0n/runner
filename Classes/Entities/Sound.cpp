//
// Created by Master Móviles on 06/04/2017.
//

#include "Sound.hpp"
#include <stdlib.h>
#include <vector>
#include <iostream>

Entities::Sound*  Entities::Sound::instance = NULL;

void Entities::Sound::stopSound(std::string sound) {

    this->audio->stopEffect((unsigned int)this->mapSounds[sound]);
    this->mapSounds[sound] = -1;
}

void Entities::Sound::stopBackground(std::string sound) {

    this->audio->stopBackgroundMusic(true);
}

void Entities::Sound::playSound(std::string sound) {

    this->mapSounds[sound] = audio->playEffect(sound.c_str());
}

void Entities::Sound::playBackground(std::string sound){

    audio->playBackgroundMusic(sound.c_str(),true);
}

void Entities::Sound::pauseBackground(){
    
    audio->pauseBackgroundMusic();
}

void Entities::Sound::resumeBackground(){
    
    audio->resumeBackgroundMusic();
}

void Entities::Sound::clearSounds(){

    for(int i = 0; i<soundVector.size();i++){
        this->audio->stopEffect(i);
    }
}

Entities::
Sound::Sound() {

    this-> audio = CocosDenshion::SimpleAudioEngine::getInstance();
    this->mapSounds.reserve(soundVector.size());
    for(int i = 0; i<soundVector.size();i++){
        this->audio->preloadEffect(soundVector.at(i).c_str());
        this->mapSounds[soundVector.at(i).c_str()] = -1;
    }

    this->mapBackground["background.mp3"] = -1;
}

Entities::Sound*
Entities::
Sound::getInstance()
{
    if(instance==NULL) {
        instance = new Entities::Sound();
    }
    return instance;
}

CocosDenshion::SimpleAudioEngine* Entities::Sound::getAudio() {
    return this->audio;
}
