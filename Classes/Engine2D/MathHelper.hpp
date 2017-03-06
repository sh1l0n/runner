//
// Created by Master Móviles on 6/3/17.
//

#ifndef MYGAME_MATHHELPER_H
#define MYGAME_MATHHELPER_H

class MathHelper {

public:
    static bool rectCollision(
            float x1,
            float y1,
            float width1,
            float height1,
            float x2,
            float y2,
            float width2,
            float height2);

};


#endif //MYGAME_MATHHELPER_H
