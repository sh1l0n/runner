//
// Created by juancarlos on 26/02/17.
//

#include "RootEntity.hpp"

RootEntity::RootEntity() {
    x, dx, lx = getPositionX();
    y, dy, ly = getPositionY();
    motionX = 6.f;
    motionY = 0.f;
    stepTime, deltaCount = 0.f;

    //test
    x = 32.f;
    y = 200.f;
}

/*!
 * Complex game logic (like movement, collision, generation etc..) should be here to be executed 15 frames per second.
 * This implementation allows the game to process heavy mathematical operations and maintain a stable frame rate.
 * @param delta frame duration in seconds
 */

void RootEntity::update(float delta) {

    deltaCount += 0.016; // FIXME: Corregir problema con delta (es muy invariable y ejecuta el update 4 0 5 veces, desestabilizando el movimiento)
    //deltaCount += delta;
    if(deltaCount >= 1/15.f) {
        lx = x;
        ly = y;

        x = x + motionX;
        y = y + motionY;

        stepTime = deltaCount;
        deltaCount = 0.f;
    }

}

/*!
 * All drawing functions should be here to be executed 60 frames per second. This method uses frame interpolation
 * to generate smooth movements
 * @param delta frame duration in seconds
 */
void RootEntity::draw(float delta) {
    float percenTick = 0.f;

    if(stepTime!=0) { //Se salta el primer frame
        percenTick = deltaCount / stepTime;
    } else {
        percenTick = 0;
    }

    dx = lx*(1.f-percenTick) + x * percenTick;
    dy = ly*(1.f-percenTick) + y * percenTick;

    setPosition(dx, dy);


}
void RootEntity::setSprite(const std::string &filename) {
    sprite = Sprite::create(filename);
    this->addChild(sprite);
}

RootEntity * RootEntity::create()
{
    RootEntity * ret = new (std::nothrow) RootEntity();
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