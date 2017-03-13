//
// Created by Master Móviles on 27/2/17.
//

#include <iostream>
#include <Engine2D/MathHelper.hpp>
#include "Player.hpp"

using namespace std;

Player::Player():RootEntity() {
    vx = 0;
    vy = 0;
    accel = 3.f;
    jump = 40.f;
    jumpSpeed = 20.f;
    friction = 1.f;
    maxVel = 20.f;
    gravity = 6.f;
    terminalVelocity = 5;
    maxJump = 40.f;
    auxHeight = 0;
    floor = false;
    bend = false;
    jumpTime = true;

    debug = true;

    if(debug) {
        drawNode->drawRect(Vec2(0 - 20 , 0 - 20 ), Vec2(20, 20), Color4F::RED);
        //drawNode->drawRect(Vec2(0 - getWidth() / 2, 0 - getHeight() / 2), Vec2(20, 20), Color4F::WHITE);
    }

}

void Player::customupdate(float delta) {
    this->beginUpdate();
    if(moveRight) {
        vx += accel;
        if(vx > maxVel ) vx = maxVel;
    } else if(!moveLeft) {
        if (vx >= friction) vx -= friction;
        else if(vx < friction && vx > 0) vx = 0;
    }

    if(moveLeft) {
        vx -= accel;
        if(vx < -maxVel) vx = -maxVel;
    } else if(!moveRight) {
        if(vx <= -friction) vx+=friction;
        else if(vx > -friction && vx < 0) vx = 0;
    }

    // Salto
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

    if(moveDown && !bend){
        auxHeight = getHeight();
        setHeight(auxHeight/2);
        bend = true;
    }else if(!moveDown && bend){
        setHeight(auxHeight);
        bend = false;
    }

    vy -= gravity;

    resolveFloorCollisionsX();
    setMotionX(vx);

    resolveFloorCollisionsY();
    setMotionY(vy);

    RootEntity::customupdate(delta);
}

void Player::customdraw(float delta, float deltaCount, float stepTime) {
    drawNode->drawRect(Vec2(0 - getWidth()/2 , 0 - getHeight()/2 ), Vec2(getWidth()/2, getHeight()/2), Color4F::RED);
    RootEntity::customdraw(delta, deltaCount, stepTime);
}

void Player::setFloorCollision(Vector<RootEntity *> floors) {
    floorVector = floors;
}


void Player::resolveFloorCollisionsY() {
    for(int i = 0; i<floorVector.size(); i++) {
        RootEntity *block = floorVector.at(i);
        //Vertical collision
        if (MathHelper::rectCollision(getCorrectPositionX(), getCorrectPositionY() + vy, getWidth(), getHeight(),
                                      block)) {

            if(getCorrectPositionY() + getHeight() > block->getCorrectPositionY()) {
                floor = true;
                jumpTime = true;
                jumpSpeed = 30.f;
                setY(block->getCorrectPositionY() + block->getHeight() + getHeight()/2);
            } else {
                jumpSpeed = 30.f;
                jumpTime = false;
                setY(block->getCorrectPositionY() - getHeight()/2);
            }

            vy = 0;
        }
    }
}

void Player::resolveFloorCollisionsX() {
    for(int i = 0; i<floorVector.size(); i++) {
        RootEntity* block = floorVector.at(i);

        //Horizontal collision
        if(MathHelper::rectCollision(getCorrectPositionX() + vx, getCorrectPositionY(), getWidth(), getHeight(), block)) {

            if(getCorrectPositionX() + getWidth() > block->getCorrectPositionX() + block->getWidth()/2.f) {
                setX(block->getCorrectPositionX() + block->getWidth() + getWidth()/2);
            } else {
                setX(block->getCorrectPositionX() - getWidth()/2);
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