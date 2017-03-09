//
// Created by juancarlos on 26/02/17.
//

#include <iostream>
#include "RootEntity.hpp"

using namespace std;

RootEntity::RootEntity() {
    debug = false;
    x, dx, lx = getPositionX();
    y, dy, ly = getPositionY();
    width, height = 0;
    motionX = 0.f;
    motionY = 0.f;
    stepTime, deltaCount = 0.f;

    drawNode = DrawNode::create();
    this->addChild(drawNode);
}

/*!
 * Complex game logic (like movements, collisions, generation etc..) should be here to be executed 15 frames per second.
 * This implementation allows the game to process heavy mathematical operations and maintain a stable drawing frame rate.
 * @param delta frame duration in seconds
 */
void RootEntity::customupdate(float delta) {

    deltaCount += 0.016; // FIXME: Corregir problema con delta (es muy invariable y ejecuta el update 4 0 5 veces, desestabilizando el movimiento)
    //deltaCount += delta;

    //fifteen frames per second
    if(deltaCount >= 0.067) {
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

    //step the first frame
    if(stepTime!=0) {
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
void RootEntity::setX(float x){
    this->x = x;
    //this->lx = x;
    //this->dx = x;
}

void RootEntity::setY(float y){
    this->y = y;
    //this->ly = y;
    //this->dy = y;
}
void RootEntity::setPosition(float x, float y) {
    this->x = x;
    this->y = y;
    this->lx = x;
    this->ly = y;
    this->dx = x;
    this->dy = y;
    Node::setPosition(x, y);
}

/*!
 * Image loaded on the player and set the bounding box
 * @param filename player image name
 */
void RootEntity::setSprite(const std::string &filename) {
    sprite = Sprite::create(filename);
    this->width = sprite->getContentSize().width;
    this->height = sprite->getContentSize().height;
    this->addChild(sprite);
}

void RootEntity::setHeight(float height) {
    this->height = height;
}

//GETTERS

float RootEntity::getX() {
    return this->x;
}

float RootEntity::getY() {
    return this->y;
}

float RootEntity::getMotionX() {
    return this->motionX;
}

float RootEntity::getMotionY() {
    return this->motionY;
}

float RootEntity::getWidth() {
    return this->width;
}

float RootEntity::getHeight() {
    return this->height;
}

bool RootEntity::isDebug() {
    return this->debug;
}

/*!
 * Get horitzontal center position of the player
 */
float RootEntity::getCorrectPositionX() {
    return this->x - this->width/2;
}

float RootEntity::getCorrectPositionY() {
    return this->y - this->height/2;
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