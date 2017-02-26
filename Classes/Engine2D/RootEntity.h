//
// Created by juancarlos on 26/02/17.
//

#ifndef MYGAME_ROOTENTITY_H
#define MYGAME_ROOTENTITY_H

#include "cocos2d.h"
USING_NS_CC;

class RootEntity: public Node {
private:
    float x, y, ax, ay, lax, lay, dx, dy, lx, ly;
    float motionX, motionY;
    float deltaCount, stepTime, time, totalTime;
    Sprite *sprite;
public:
    RootEntity();
    static RootEntity * create();

    void update(float delta);
    void draw(float delta);

    void setSprite(const std::string &filename);
};


#endif //MYGAME_ROOTENTITY_H
