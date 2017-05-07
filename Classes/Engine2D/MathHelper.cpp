//
// Created by Master Móviles on 6/3/17.
//

#include <iostream>
#include "MathHelper.hpp"
#include "../Scenes/PlayerTestScene.hpp"

/*bool MathHelper::rectCollision(float x1, float y1, float width1, float height1,
                               float x2, float y2, float width2, float height2) {
    if(x1 + width1 > x2 && x1 < x2 + width2) {
        if (y1 + height1 > y2 && y1 < y2 + height2) {
            return true;
        }
    }
    return false;
}*/

MathHelperTypeCollision
MathHelper::rectCollision(float x, float y, float width, float height, TiledMap::BasicBlock *e2) {
    
    if(x + width > e2->getX() && x < e2->getX() + e2->getWidth()) {
        Color4F white(1, 0, 0, 1);
        if (y + height > e2->getY() &&  y < e2->getY() + e2->getHeight()) {
            if(e2->_type == TiledMap::TypeBlock::COIN) {
                return MathHelperTypeCollision::COIN;
            }
            return MathHelperTypeCollision::COLLISION;
        }
    }
    return MathHelperTypeCollision::NONE;
}

int MathHelper::sign(float x) {
    return x > 0 ? 1 : -1;
}
