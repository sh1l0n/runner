//
// Created by Master Móviles on 20/03/2017.
//

#ifndef MYGAME_MAINMENU_HPP
#define MYGAME_MAINMENU_HPP

#include <audio/include/SimpleAudioEngine.h>
#include "cocos2d.h"

/**
* Size of the sprites
*/
const static unsigned short int K_DEFAULT_SIZE_SPRITE = 70;

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
    Sprite * getSubImage(int x, int y);
    void putImagePosition(Sprite *sprite, int x, int y, int pos);

    CREATE_FUNC(MainMenu);
};

#endif //MYGAME_MAINMENU_HPP
