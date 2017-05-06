//
// Created by Master Móviles on 27/2/17.
//

#include <iostream>
#include "../Engine2D/MathHelper.hpp"
#include "Player.hpp"

USING_NS_CC;

Player::Player():RootEntity() {
    vx = vy = 0;
    accel = 2.0f;
    jump = 30.f;
    initialJumpSpeed = 15.f;
    jumpSpeed = initialJumpSpeed;
    friction = 1.f;
    maxVel = 0.f; //Speed marker velocity;
    gravity = 3.f;
    terminalVelocity = 5;
    maxJump = 100.f;
    auxHeight = 0;
    floor = false;
    bend = false;
    jumpTime = true;
    animationSpeed = 0;
    moveLeft = moveRight = moveUp = moveDown = floor = bend = jumpTime = false;
    debug = false;
    speedMarkerVelocity = 0;
    speedMarkerPosition = 0;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player/player_walk.plist");
    auto frames = getAnimation("p1_walk%02d.png", 6);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    this->setSprite(sprite);

    this->animation = Animation::createWithSpriteFrames(frames, 1.0f/8);
    sprite->runAction(RepeatForever::create(Animate::create(this->animation)));
    //Pablo
   
    this->scaleSprite(1, 1);
    this->setWidth((sprite->getContentSize().width-sprite->getContentSize().width/5)*1);
    this->setHeight((sprite->getContentSize().height-6)*1);
}

/*!
 * RootEntity custom update method reimplementation
 * @param delta
 */
void Player::customupdate(float delta) {
    this->beginUpdate(); //must be called on every update reimplementation
    
    if(getX() >= speedMarkerPosition) {
        maxVel = speedMarkerVelocity/0.36f;
    } else {
         maxVel = speedMarkerVelocity/0.3f;
    }
    

    // Right movement
    if(moveRight) {
        vx += accel;
        if(vx > maxVel ) vx = maxVel;
    } else if(!moveLeft) {
        if (vx >= friction) vx -= friction;
        // else if(vx < friction && vx > 0) vx = 0;
    }

    // Left movement
    if(moveLeft) {
        vx -= accel;
        if(vx < -maxVel) vx = -maxVel;
    } else if(!moveRight) {
        if(vx <= -friction) vx+=friction;
        // else if(vx > -friction && vx < 0) vx = 0;
    }
    
    // horizontal movement
    if (vx < maxVel) {
        vx += 2.f;
    } else {
        vx = maxVel;
    }

    // Jump
    if(moveUp){
        if(jumpTime){
            if(vy < maxJump) {
                vy += jumpSpeed;
                jumpSpeed = jumpSpeed/2.2f;
            } else {
                vy = maxJump;
                jumpTime = false;
            }
        }
        floor = false;
    } else {
        if(!floor) {
            jumpTime = false;
        }
    }

    // Bend
    /* if(moveDown && !bend){
        auxHeight = getHeight();
        setHeight(auxHeight/2);
        bend = true;
    }else if(!moveDown && bend){
        setHeight(auxHeight);
        bend = false;
    } */

    // Applies the gravity
    vy -= gravity;
    
    resolveFloorCollisionsX(); // horizontal collisions
    setMotionX(vx);

    resolveFloorCollisionsY(); // vertical collisions
    setMotionY(vy);
    
    // Remove unused collisionables
   
    for(auto it2 = floorVector.begin(); it2 != floorVector.end();)
    {
        if((*it2)->getX() < getX() - 100)
        {
            it2 = floorVector.erase(it2);
        }
        else
        {
            ++it2;
        }
    }
    

    log("SPVEL: %f", speedMarkerVelocity);
    RootEntity::customupdate(delta);
}


/*!
 * RootEntity custom draw method reimplementation
 * @param delta
 * @param deltaCount
 * @param stepTime
 */
void Player::customdraw(float delta, float deltaCount, float stepTime) {
    
   // walk->setPosition(this->getX(), this->getY());
    RootEntity::customdraw(delta, deltaCount, stepTime);
}

/*!
 * Sets the collisionable objects array
 * @param floors
 */
void Player::setFloorCollision(std::vector<TiledMap::BasicBlock *> floors) {
    floorVector.insert(floorVector.end(), floors.begin(), floors.end());
}


void Player::resolveFloorCollisionsY() {
    for(int i = 0; i<floorVector.size(); ++i) {
        TiledMap::BasicBlock *block = floorVector.at(i);
        //Vertical collision
        if (MathHelper::rectCollision(getCorrectPositionX(), getCorrectPositionY() + vy, getWidth(), getHeight(),
                                      block)) {

            if(getCorrectPositionY() + getHeight() > block->getY()) {
                floor = true;
                jumpTime = true;
                jumpSpeed = initialJumpSpeed;
                if(vy < 0){
                    log("UP v-");
                    setY(block->getY() + block->getHeight() + getHeight()/2);
                } else {
                    log("UP v+");
                    setY(block->getY() - getHeight()/2);
                }
                //pab
                if(block->_type==TiledMap::TypeBlock::SPIKE){
                    jumpSpeed = 20.f;
                    if(vx>0){
                        vx=vx-2;
                    }
                }
                //fin pab

            } else {
                jumpSpeed = 30.f;
                jumpTime = false;
                if(vy > 0) {
                    log("DOWN v+");
                    setY(block->getY() - getHeight() / 2);
                } else {
                    log("DOWN v-");
                    setY(block->getY() + block->getHeight() + getHeight()/2);
                }
            }

            vy = 0;
        }
    }
}

void Player::resolveFloorCollisionsX() {
    for(int i = 0; i<floorVector.size(); ++i) {
        TiledMap::BasicBlock *block = floorVector.at(i);

        //Horizontal collision
        if(MathHelper::rectCollision(getCorrectPositionX() + vx, getCorrectPositionY(), getWidth(), getHeight(), block)) {

            if(getCorrectPositionX() + getWidth() > block->getX() + block->getWidth()/2.f) {
                if(vx < 0) {
                    setX(block->getX() + block->getWidth() + getWidth() / 2);
                } else {
                    setX(block->getX() - getWidth()/2);
                }
            } else {
                if(vx > 0) {
                    setX(block->getX() - getWidth()/2);
                } else {
                    setX(block->getX() + block->getWidth() + getWidth() / 2);
                }

            }
            
            vx = 0;
        }
    }
}

void Player::onKeyLeft() {
    moveLeft = true;
}

void Player::onKeyRight() {
    moveRight = true;
}

void Player::onKeyUp() {
    moveUp = true;
}

void Player::onKeyDown() {
    moveDown = true;
}

void Player::onKeyLeftRelease() {
    moveLeft = false;
}

void Player::onKeyRightRelease() {
    moveRight = false;
}

void Player::onKeyUpRelease(){
    moveUp = false;
}

void Player::onKeyDownRelease(){
    moveDown = false;
}

Player * Player::create()
{
    Player * ret = new (std::nothrow) Player();
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

Vector<SpriteFrame*> Player::getAnimation(const char *format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void Player::setSpeedMarkerVelocity(float velocity) {
    speedMarkerVelocity = velocity;
}

void Player::setSpeedMarkerPosition(float position) {
    speedMarkerPosition = position;
}
