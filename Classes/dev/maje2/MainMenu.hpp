//
// Created by Master Móviles on 20/03/2017.
//

#ifndef MYGAME_MAINMENU_HPP
#define MYGAME_MAINMENU_HPP

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void closeMenuCallback(cocos2d::Ref* sender);
    void playMenuCallback(cocos2d::Ref* sender);

    CREATE_FUNC(MainMenu);
};

#endif //MYGAME_MAINMENU_HPP
