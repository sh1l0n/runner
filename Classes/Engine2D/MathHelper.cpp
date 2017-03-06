//
// Created by Master Móviles on 6/3/17.
//

#include <iostream>
#include "MathHelper.hpp"

bool MathHelper::rectCollision(float x1, float y1, float width1, float height1, float x2, float y2, float width2,
                                      float height2) {
    if(x1 + width1 > x2 && x1 < x2 + width2) {
        if (y1 + height1 > y2 && y1 < y2 + height2) {
            return true;
        }
    }
    return false;
}