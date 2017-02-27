//
// Created by Master Móviles on 27/2/17.
//

#include "Player.hpp"

Player::Player():RootEntity() {

}

void Player::customupdate(float delta) {
    RootEntity::customupdate(delta);
}

void Player::customdraw(float delta) {
    RootEntity::customdraw(delta);
}

void Player::moveLeft() {
    setMotionX(-6.f);
}

void Player::moveRight() {
    setMotionX(6.f);
}

void Player::stop() {
    setMotionX(0);
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