//
// Created by Master Móviles on 27/2/17.
//

#include <iostream>
#include "Player.hpp"

using namespace std;

Player::Player():RootEntity() {
    vx = 0;
    vy = 0;
    accel = 0.5;
    jump = 25;
    friction = 0.3;
    maxVel = 15;
    gravity = 0.8;
    terminalVelocity = 5;
    floor = false;
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

    //modo vuelo
    /*if(moveUp){
        floor = false;
        vy += 1.5;
    }*/

    if(moveUp){
        if(floor){
            vy = jump;
        }
        floor = false;
    }

    if(!floor) {
        //if floor collision
        if(getCorrectPositionY() < 0) {
            setY(0 + getHeight()/2); //FIXME:cambiar el 0 por la altura en la que esté la plataforma
            vy = 0;
            floor = true;
        }else{
            vy -= gravity;
        }
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

void Player::onKeyUp() {
    moveUp = true;
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