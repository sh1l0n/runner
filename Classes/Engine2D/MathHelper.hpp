//
// Created by Master Móviles on 6/3/17.
//

#pragma once
#include "TiledMap/BasicBlock.hpp"

enum MathHelperTypeCollision {
    NONE,
    COLLISION,
    COIN
};

class MathHelper {

public:
    static MathHelperTypeCollision rectCollision(float x, float y, float width, float height, TiledMap::BasicBlock *e2);
    static int sign(float x);

};

