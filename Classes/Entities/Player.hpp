//
// Created by Master Móviles on 27/2/17.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H


#include <Engine2D/RootEntity.hpp>

class Player : public RootEntity {
private:
    float accel, maxVel, friction, gravity, terminalVelocity, jump;
    float vx, vy;
    bool moveLeft, moveRight, moveUp, floor;
public:
    Player();
    static Player * create();

    void customupdate(float delta) override;
    void customdraw(float delta) override;

    void onKeyLeft();
    void onKeyRight();
    void onKeyUp();
    void onKeyLeftRelease();
    void onKeyRightRelease();
    void onKeyUpRelease();
};


#endif //MYGAME_PLAYER_H
