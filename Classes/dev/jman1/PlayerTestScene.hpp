//
// Created by juancarlos on 26/02/17.
//

#pragma once

#include "../../Engine2D/RootEntity.hpp"
#include "cocos2d.h"
USING_NS_CC;

class PlayerTestScene: public Layer {

public:
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    static cocos2d::Scene* createScene();

    void update(float) override;
    CREATE_FUNC(PlayerTestScene);

private:
    RootEntity* _player;
    int _posXStartNewChunck;
    //std::vector<TiledMap::Chunck> _chunckVector;
};

