//
// Created by Master Móviles on 20/03/2017.
//

#pragma once

#include <audio/include/SimpleAudioEngine.h>
#include "cocos2d.h"

namespace Scenes {
    
    /**
    * Size of the sprites
    */
    const static unsigned short int K_DEFAULT_SIZE_SPRITE = 70;
    const static unsigned short int K_DEFAULT_SIZE_SPRITE_PHONE = 35;

    /**
    * Class MainMenu for generating the first scene
    */
    class MainMenu : public cocos2d::Layer{
    public:
        static cocos2d::Scene* createScene();
        //static CocosDenshion::SimpleAudioEngine* audio;

        virtual bool init();

        void closeMenuCallback(cocos2d::Ref* sender);
        void playMenuCallback(cocos2d::Ref* sender);
        cocos2d::Sprite * getSubImage(int x, int y);
        void putImagePosition(cocos2d::Sprite *sprite, int x, int y, int pos);

        CREATE_FUNC(MainMenu);
    };

}
