//
// Created by juancarlos on 26/02/17.
//

#ifndef MYGAME_PLAYERTEST_H
#define MYGAME_PLAYERTEST_H

#include <Engine2D/RootEntity.h>
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
    RootEntity *e;
    cocos2d::Sprite *test;
    float testX = 0;
};


#endif //MYGAME_PLAYERTEST_H
