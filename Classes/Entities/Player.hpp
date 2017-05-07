//
// Created by Master Móviles on 27/2/17.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H

#include <iostream>
#include "../Engine2D/RootEntity.hpp"
#include "../Engine2D/TiledMap/TiledMapGenerator.hpp"
#include "../Engine2D/TiledMap/ConstantDevices.hpp"

#include "cocos2d.h"
USING_NS_CC;

class Player : public RootEntity {
private:
    //! x coordinate velocity
    float vx;
    //! y coordinate velocity
    float vy;
    //! Speed acceleration
    float accel;
    //! maximum horizontal velocity
    float maxVel;
    //! air friction
    float friction;
    //! gravity speed
    float gravity;
    //! Maximum vertical fall velocity
    float terminalVelocity;
    //! max jump speed
    float jump;
    //! Saves original heigh
    float auxHeight;
    //! Maximum jump speed
    float maxJump;
    //! jump speed
    float jumpSpeed;
    float initialJumpSpeed;
    
    float speedMarkerVelocity;
    float speedMarkerPosition;

    bool moveLeft, moveRight, moveUp, moveDown, floor, bend, jumpTime;

    //Textures
    std::string texStand = "test/Basepack/player/p1_stand.png";
    std::string texDuck = "test/Basepack/player/p1_duck.png";
    std::string textHurt = "test/Basepack/player/p1_hurt.png";
    std::string texJump = "test/Basepack/player/p1_jump.png";

    //Animations
    SpriteBatchNode* walk;
    Sprite* sprWalk;

    //! Vector which stores collisionable floor objects
    std::vector<TiledMap::BasicBlock*> floorVector;
    void resolveFloorCollisionsY();
    void resolveFloorCollisionsX();

    Vector<SpriteFrame*> getAnimation(const char *format, int count);
    Animation *animation;
    float animationSpeed;
public:
    Player();
    static Player * create();

    void customupdate(float delta) override;
    void customdraw(float delta, float deltaCount, float stepTime) override;
    void setFloorCollision(std::vector<TiledMap::BasicBlock*> floors);
    void setSpeedMarkerVelocity(float velocity);
    void setSpeedMarkerPosition(float position);

    void onKeyLeft();
    void onKeyRight();
    void onKeyUp();
    void onKeyDown();
    void onKeyLeftRelease();
    void onKeyRightRelease();
    void onKeyUpRelease();
    void onKeyDownRelease();
};


#endif //MYGAME_PLAYER_H
