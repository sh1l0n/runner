//
// Created by Master Móviles on 27/2/17.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H


#include <Engine2D/RootEntity.hpp>

class Player : public RootEntity {
private:
    float accel, maxVel, friction, gravity, terminalVelocity, jump, auxHeight, maxJump, jumpSpeed;
    float vx, vy;
    bool moveLeft, moveRight, moveUp, moveDown, floor, bend, jumpTime;

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
