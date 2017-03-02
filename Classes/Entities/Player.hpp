//
// Created by Master Móviles on 27/2/17.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H


#include <Engine2D/RootEntity.hpp>

class Player : public RootEntity {
private:
    float accel, maxVel, friction, gravity, terminalVelocity;
    float vx, vy;
    bool moveLeft, moveRight;
public:
    Player();
    static Player * create();

    void customupdate(float delta) override;
    void customdraw(float delta) override;

    void onKeyLeft();
    void onKeyRight();
    void onKeyLeftRelease();
    void onKeyRightRelease();
};


#endif //MYGAME_PLAYER_H
