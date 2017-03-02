//
// Created by Pablo Ramon on 2/3/17.
//

#pragma once
#include "cocos2d.h"
USING_NS_CC;
namespace TileMap {
    class TileCollisionable : public Node {
    private:
       float _lx;
        float _ly;
        float _gx;
        float _gy;
        float _width;
        float _height;
    public:
        TileCollisionable(const float localX = 0, const float localY = 0, const float width = 0, const float height = 0);

        void setGlobalBoundingBox(const float posX, const float posY);

        Rect getGlobalBoundingBox() const;

        TileMap::TileCollisionable& operator=(const TileCollisionable& tileCollisionable);
    };
}



