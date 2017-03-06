//
// Created by juancarlos on 26/02/17.
//

#pragma once

#include "cocos2d.h"
USING_NS_CC;

class RootEntity: public Node {
private:

    float x, y;
    float dx, dy;
    float lx, ly;
    float motionX, motionY;
    float deltaCount, stepTime, time, totalTime;
    Sprite *sprite;
public:
    RootEntity();
    RootEntity(const RootEntity& object);
    static RootEntity * create();

    void update(float delta);
    void draw(float delta);

    void setSprite(const std::string &filename);
};

