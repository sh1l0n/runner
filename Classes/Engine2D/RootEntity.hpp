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
    float deltaCount, stepTime;
    Sprite *sprite;

public:
    RootEntity();
    static RootEntity * create();

    void update(float delta);
    void draw(float delta);

    //Getters
    void setPosition(float x, float y);
    float getMotionX() const;
    void setMotionY(float motionY);
    void setSprite(const std::string &filename);

    //Setters
    void setMotionX(float motionX);
    float getMotionY() const;


};

