//
// Created by juancarlos on 26/02/17.
//

#pragma once

#include "../../Entities/Player.hpp"
#include "../../Engine2D/TiledMap/BasicBlock.hpp"
#include "../../Engine2D/RootEntity.hpp"
#include "cocos2d.h"

USING_NS_CC;

class PlayerTestScene: public Layer {

public:
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    static cocos2d::Scene* createScene();

    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

    void update(float) override;
    CREATE_FUNC(PlayerTestScene);

private:

    float deltaCount, stepTime;

    Player *e;
    RootEntity *box;

    Vector<TiledMap::BasicBlock*> boxes;

};

