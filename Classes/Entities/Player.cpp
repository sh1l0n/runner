//
// Created by Master Móviles on 27/2/17.
//

#include <iostream>
#include "../Engine2D/MathHelper.hpp"
#include "Player.hpp"

USING_NS_CC;

Player::Player():RootEntity() {
    vx = vy = 0;
    accel = 3.f;
    jump = 40.f;
    jumpSpeed = 20.f;
    friction = 1.f;
    maxVel = 8.5f;
    gravity = 6.f;
    terminalVelocity = 5;
    maxJump = 40.f;
    auxHeight = 0;
    floor = false;
    bend = false;
    jumpTime = true;
    animationSpeed = 0;
    moveLeft = moveRight = moveUp = moveDown = floor = bend = jumpTime = false;
    debug = false;

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("player/player_walk.plist");
    auto frames = getAnimation("p1_walk%02d.png", 6);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    this->setSprite(sprite);

    this->animation = Animation::createWithSpriteFrames(frames, 1.0f/8);
    sprite->runAction(RepeatForever::create(Animate::create(this->animation)));
    this->setWidth((sprite->getContentSize().width-sprite->getContentSize().width/5)/2);
    this->setHeight((sprite->getContentSize().height-6)/2);
    //Pablo
   
    this->scaleSprite(0.5f, 0.5f);
    this->scaleSprite(TiledMap::ConstanDevices::getInstance()->FACTOR_SCALE, TiledMap::ConstanDevices::getInstance()->FACTOR_SCALE);
}

/*!
 * RootEntity custom update method reimplementation
 * @param delta
 */
void Player::customupdate(float delta) {
    this->beginUpdate(); //must be called on every update reimplementation

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

    RootEntity::customupdate(delta);
    std::cout<< "#" << floorVector.size() << std::endl;
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
    floorVector = floors;
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
                jumpSpeed = 30.f;
                if(vy < 0){
                    log("UP v-");
                    setY(block->getY() + block->getHeight() + getHeight()/2);
                } else {
                    log("UP v+");
                    setY(block->getY() - getHeight()/2);
                }

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
        cocos2d::log("%s", str);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}
