//
// Created by juancarlos on 26/02/17.
//

#include <iostream>
#include "RootEntity.hpp"

using namespace std;

RootEntity::RootEntity() {
    debug = false;
    /*!
     * x, y:    Logic x, y position
     * dx, dy:  drawing x, y position
     * lx, ly:  Last frame x, y position
     */
    x, dx, lx = getPositionX();
    y, dy, ly = getPositionY();


    width, height = 0; // Bounding box width and height
    motionX, motionY = 0; // Motion (speed) for x and y coordinates.

    stepTime = 0.f; // Duration between each update iteration (in milliseconds)

    /*!
     * deltaCount accumulates the time (in milliseconds) between each update iteration. It starts in 0 every time a
     * new update iteration begins and is incremented 'delta' millisecons  for each drawing frame. (delta is the amount
     * of time which every draw frame takes)
     */
    deltaCount = 0.f;

    drawNode = DrawNode::create();
    this->addChild(drawNode);
}

/*!
 * Complex game logic (like movements, collisions, generation etc..) should be here to be executed 15 frames per second.
 * This implementation allows the game to process heavy mathematical operations and maintain a stable drawing frame rate.
 * @param delta frame duration in seconds
 */
void RootEntity::customupdate(float delta) {

    x = x + motionX;
    y = y + motionY;
    stepTime = deltaCount;
}

/*!
 * This method needs to be called at the very beginning of any update reimplementation. It saves the last frame x y
 * coordinates that needs to be used on drawing interpolation.
 */
void RootEntity::beginUpdate() {
    lx = x;
    ly = y;
}


/*!
 * All drawing functions should be here to be executed 60 frames per second. This method uses frame interpolation
 * to generate smooth movements
 * @param delta frame duration in seconds
 */
void RootEntity::customdraw(float delta, float deltaCount, float stepTime) {
    float percenTick = 0.f;

    //skip the first frame to avoid 0 division
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
 * @param motionX Horizontal speed movement
 */
void RootEntity::setMotionX(float motionX) {
    RootEntity::motionX = motionX;
}

/*!
 * Sets motion y (vertical movement)
 * @param motionY Vertical speed movement
 */
void RootEntity::setMotionY(float motionY) {
    RootEntity::motionY = motionY;
}

/*!
 * Sets x position (interpolated)
 * @param x Logic x position
 */
void RootEntity::setX(float x){
    this->x = x;
}


/*!
 * Sets y postion (interpolated)
 * @param y Logic y position
 */
void RootEntity::setY(float y){
    this->y = y;
}

/*!
 * Sets x y logic position (NO interpolated)
 * @param x Logic y position
 * @param y Logic x position
 */
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
 * Adds a sprite node and sets the bounding box using the provided image width and height
 * @param filename Image utl
 */
void RootEntity::setSprite(Sprite *sprite) {
    this->sprite = sprite;
    this->width = sprite->getContentSize().width;
    this->height = sprite->getContentSize().height;
    this->addChild(sprite);
}

/*!
 * Sets boundig box width
 * @param width
 */
void RootEntity::setWidth(float width) {
    this->width = width;
}

/*!
 * Sets boundig box height
 * @param width
 */
void RootEntity::setHeight(float height) {
    this->height = height;
}

//GETTERS

/*!
 * Gets left bottom corner logic x position
 */
float RootEntity::getCorrectPositionX() {
    return this->x - this->width/2;
}

/*!
 * Gets left bottom corner logic y position
 */
float RootEntity::getCorrectPositionY() {
    return this->y - this->height/2;
}

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