//
// Created by Master Móviles on 6/3/17.
//

#include <iostream>
#include "MathHelper.hpp"

/*bool MathHelper::rectCollision(float x1, float y1, float width1, float height1,
                               float x2, float y2, float width2, float height2) {
    if(x1 + width1 > x2 && x1 < x2 + width2) {
        if (y1 + height1 > y2 && y1 < y2 + height2) {
            return true;
        }
    }
    return false;
}*/

bool MathHelper::rectCollision(float x, float y, float width, float height, RootEntity *e2) {
    if(x + width > e2->getCorrectPositionX()  && x < e2->getCorrectPositionX() + e2->getWidth()) {
        if (y + height > e2->getCorrectPositionY() &&  y < e2->getCorrectPositionY() + e2->getHeight()) {
            return true;
        }
    }
    return false;
}

int MathHelper::sign(float x) {
    return x > 0 ? 1 : -1;
}