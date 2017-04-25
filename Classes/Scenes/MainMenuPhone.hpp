//
//  MainMenuPhone.hpp
//  Runner
//
//  Created by Master Móviles on 22/04/2017.
//
//

#pragma once

#include "audio/include/SimpleAudioEngine.h"
#include "../Entities/Sound.hpp"
#include "PlayerTestScene.hpp"
#include "cocos2d.h"

namespace Scenes {
    
    /**
     * Size of the sprites
     */
    //const static unsigned short int K_DEFAULT_SIZE_SPRITE = 70;
    //const static unsigned short int K_DEFAULT_SIZE_SPRITE_PHONE = 35;
    
    /**
     * Class MainMenu for generating the first scene
     */
    class MainMenuPhone : public cocos2d::Layer{
    private:
        const Size SIZE_PICTURE_IPHONE = Size(480,296);
        const Size WINDOWS_SIZE_IPHONE = Director::getInstance()->getWinSize();
    public:
        MainMenuPhone();
        ~MainMenuPhone();
        static cocos2d::Scene* createScene();
        //static CocosDenshion::SimpleAudioEngine* audio;
        
        virtual bool init();
        
        void closeMenuCallback(cocos2d::Ref* sender);
        void playMenuCallback(cocos2d::Ref* sender);
        CREATE_FUNC(MainMenuPhone)
    };

}
