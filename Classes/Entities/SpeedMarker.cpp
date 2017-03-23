//
// Created by Pablo Ramon on 23/3/17.
//

#include "SpeedMarker.hpp"

#include <iostream>
#include <Engine2D/MathHelper.hpp>
#include "Player.hpp"

using namespace std;

SpeedMarker::SpeedMarker():RootEntity() {
    vx=40;


    debug = true;

    if(debug) {
        drawNode->drawRect(Vec2(0 - 20 , 0 - 20 ), Vec2(20, 20), Color4F::RED);
        //drawNode->drawRect(Vec2(0 - getWidth() / 2, 0 - getHeight() / 2), Vec2(20, 20), Color4F::WHITE);
    }

}

/*!
 * RootEntity custom update method reimplementation
 * @param delta
 */
void SpeedMarker::customupdate(float delta) {
    this->beginUpdate(); //must be called on every update reimplementation


    setMotionX(vx);
    RootEntity::customupdate(delta);
}


/*!
 * RootEntity custom draw method reimplementation
 * @param delta
 * @param deltaCount
 * @param stepTime
 */
void SpeedMarker::customdraw(float delta, float deltaCount, float stepTime) {
    drawNode->drawRect(Vec2(0 - getWidth()/2 , 0 - getHeight()/2 ), Vec2(getWidth()/2, getHeight()/2), Color4F::RED);
    RootEntity::customdraw(delta, deltaCount, stepTime);
}



SpeedMarker * SpeedMarker::create()
{
    SpeedMarker * ret = new (std::nothrow) SpeedMarker();
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
