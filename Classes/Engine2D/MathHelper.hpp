//
// Created by Master Móviles on 6/3/17.
//

#ifndef MYGAME_MATHHELPER_H
#define MYGAME_MATHHELPER_H

#include "RootEntity.hpp"

class MathHelper {

public:
    static bool rectCollision(float x, float y, float width, float height, RootEntity *e2);
    static int sign(float x);

};


#endif //MYGAME_MATHHELPER_H
