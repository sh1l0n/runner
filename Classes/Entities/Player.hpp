//
// Created by Master Móviles on 27/2/17.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H


#include <Engine2D/RootEntity.hpp>

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

    bool moveLeft, moveRight, moveUp, moveDown, floor, bend, jumpTime;

    //! Vector which stores collisionable floor objects
    Vector<RootEntity*> floorVector;
    void resolveFloorCollisionsY();
    void resolveFloorCollisionsX();
public:
    Player();
    static Player * create();

    void customupdate(float delta) override;
    void customdraw(float delta, float deltaCount, float stepTime) override;
    void setFloorCollision(Vector<RootEntity*> floors);

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
