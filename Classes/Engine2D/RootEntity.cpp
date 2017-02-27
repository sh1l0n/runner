//
// Created by juancarlos on 26/02/17.
//

#include "RootEntity.hpp"

RootEntity::RootEntity() {
    x, dx, lx = getPositionX();
    y, dy, ly = getPositionY();
    motionX = 0.f;
    motionY = 0.f;
    stepTime, deltaCount = 0.f;
}



/*!
 * Complex game logic (like movements, collisions, generation etc..) should be here to be executed 15 frames per second.
 * This implementation allows the game to process heavy mathematical operations and maintain a stable drawing frame rate.
 * @param delta frame duration in seconds
 */
void RootEntity::customupdate(float delta) {

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
void RootEntity::customdraw(float delta) {
    float percenTick = 0.f;

    if(stepTime!=0) { //Se salta el primer frame
        percenTick = deltaCount / stepTime;
    } else {
        percenTick = 0;
    }

    dx = lx*(1.f-percenTick) + x * percenTick;
    dy = ly*(1.f-percenTick) + y * percenTick;

    Node::setPosition(dx, dy);
}


//SETTERS
/*!
 * Sets motion x (horizontal movement)
 * @param motionX
 */
void RootEntity::setMotionX(float motionX) {
    RootEntity::motionX = motionX;
}

/*!
 * Sets motion y (vertical movement)
 * @param motionY
 */
void RootEntity::setMotionY(float motionY) {
    RootEntity::motionY = motionY;
}

/*!
 * Set x y position (no interpolated)
 * @param x
 * @param y
 */
void RootEntity::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    this->dx = x;
    this->dy = y;
}

void RootEntity::setSprite(const std::string &filename) {
    sprite = Sprite::create(filename);
    this->addChild(sprite);
}


//GETTERS
float RootEntity::getMotionX() const {
    return motionX;
}

float RootEntity::getMotionY() const {
    return motionY;
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