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

protected:
    DrawNode *drawNode;

public:
    RootEntity();
    static RootEntity * create();

    bool debug;

    virtual void customupdate(float delta);
    virtual void customdraw(float delta);

    //Getters
    float getCorrectPositionX();
    float getCorrectPositionY();
    float getCorrectLastPositionX();
    float getCorrectLastPositionY();
    float getMotionX();
    float getMotionY();
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    bool isDebug();

    //Setters
    void setPosition(float x, float y);
    void setX(float x);
    void setY(float y);
    void setMotionX(float motionX);
    void setMotionY(float motionY);
    void setSprite(const std::string &filename);
    void setHeight(float height);
};

