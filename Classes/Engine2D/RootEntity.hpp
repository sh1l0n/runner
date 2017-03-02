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
    float width, height;
    float motionX, motionY;
    float deltaCount, stepTime;
    Sprite *sprite;

public:
    RootEntity();
    static RootEntity * create();

    virtual void customupdate(float delta);
    virtual void customdraw(float delta);

    //Getters
    float getCorrectPositionX();
    float getCorrectPositionY();
    float getMotionX();
    float getMotionY();
    float getX();
    float getY();
    float getWidth();
    float getHeight();

    //Setters
    void setPosition(float x, float y);
    void setX(float x);
    void setY(float y);
    void setMotionX(float motionX);
    void setMotionY(float motionY);
    void setSprite(const std::string &filename);
};

