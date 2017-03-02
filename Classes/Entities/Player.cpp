//
// Created by Master Móviles on 27/2/17.
//

#include "Player.hpp"

Player::Player():RootEntity() {
    vx = 0;
    vy = 0;
    accel = 0.5;
    friction = 0.3;
    maxVel = 15;
}

void Player::customupdate(float delta) {

    if(moveRight) {
        vx += accel;
        if(vx > maxVel ) vx = maxVel;
    } else if(moveLeft == false) {
        if (vx >= friction) vx -= friction;
        else if(vx < friction && vx > 0) vx = 0;
    }

    if(moveLeft) {
        vx -= accel;
        if(vx < -maxVel) vx = -maxVel;
    } else if(moveRight == false) {
        if(vx <= -friction) vx+=friction;
        else if(vx > -friction && vx < 0) vx = 0;
    }

    setMotionX(vx);
    setMotionY(vy);

    RootEntity::customupdate(delta);
}

void Player::customdraw(float delta) {
    RootEntity::customdraw(delta);
}

void Player::onKeyLeft() {
    moveLeft = true;
}

void Player::onKeyRight() {
    moveRight = true;
}

void Player::onKeyLeftRelease() {
    moveLeft = false;
}

void Player::onKeyRightRelease() {
    moveRight = false;
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