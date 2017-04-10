//
// Created by Master Móviles on 6/3/17.
//

#pragma once
#include "TiledMap/BasicBlock.hpp"

class MathHelper {

public:
    static bool rectCollision(float x, float y, float width, float height, TiledMap::BasicBlock *e2);
    static int sign(float x);

};

