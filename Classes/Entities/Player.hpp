//
// Created by Master Móviles on 27/2/17.
//

#ifndef MYGAME_PLAYER_H
#define MYGAME_PLAYER_H


#include <Engine2D/RootEntity.hpp>

class Player : public RootEntity {
public:
    Player();
    static Player * create();

    void customupdate(float delta) override;
    void customdraw(float delta) override;

    void moveLeft();
    void moveRight();
    void stop();
};


#endif //MYGAME_PLAYER_H
