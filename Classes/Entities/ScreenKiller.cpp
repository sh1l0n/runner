//
//  ScreenKiller.cpp
//  Runner
//
//  Created by Pablo Ramon on 4/5/17.
//
//

#include "ScreenKiller.hpp"


#include <iostream>
#include "../Engine2D/MathHelper.hpp"
#include "Player.hpp"
using namespace std;

ScreenKiller::ScreenKiller():RootEntity() {
    vx=2.5;
    
    
    debug = true;
    
    if(debug) {
        int alt=Director::getInstance()->getWinSize().height;
        drawNode->drawRect(Vec2(0 - 0.05 , 0 - alt ), Vec2(0.05, alt), Color4F::RED);

        //drawNode->drawRect(Vec2(0 - 30 , 0 - 30 ), Vec2(20, 20), Color4F::GREEN);
        
    }
    
}

/*!
 * RootEntity custom update method reimplementation
 * @param delta
 */
void ScreenKiller::customupdate(float delta) {
    //this->beginUpdate(); //must be called on every update reimplementation
    
    
    //this->setPositionX(this->getPositionX()+vx);
    Node::setPosition(this->getPositionX()+vx,this->getPositionY());
    //setMotionX(vx);
    //RootEntity::customupdate(delta);
}


/*!
 * RootEntity custom draw method reimplementation
 * @param delta
 * @param deltaCount
 * @param stepTime
 */
void ScreenKiller::customdraw(float delta, float deltaCount, float stepTime) {
    //this->setPositionX(this->getPositionX()+vx);
    //setMotionX(vx);
    drawNode->drawRect(Vec2(0 - getWidth()/2 , 0 - getHeight()/2 ), Vec2(getWidth()/2, getHeight()/2), Color4F::RED);
    RootEntity::customdraw(delta, deltaCount, stepTime);
}



ScreenKiller * ScreenKiller::create()
{
    ScreenKiller * ret = new (std::nothrow) ScreenKiller();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

