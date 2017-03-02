//
// Created by Pablo Ramon on 2/3/17.
//

#include "TileCollisionable.h"

TileMap::
TileCollisionable::TileCollisionable(const float localX, const float localY, const float width, const float height) : Node() {

    this->_lx=localX;
    this->_ly=localY;
    this->_width=width;
    this->_height=height;
    this->_gx=localX;
    this->_gy=localY;
}

void
TileMap::
TileCollisionable::setGlobalBoundingBox(const float posX, const float posY) {
    this->_gx=posX+this->_lx;
    this->_gy=posY+this->_ly;
}

Rect
TileMap::
TileCollisionable::getGlobalBoundingBox() const {
    return Rect(this->_gx,this->_gy,this->_width,this->_height);

}

TileMap::TileCollisionable&
TileMap::
TileCollisionable::operator=(const TileMap::TileCollisionable& tileCollisionable) {


    this->_lx = tileCollisionable._lx;
    this->_ly = tileCollisionable._ly;
    this->_width = tileCollisionable._width;
    this->_height = tileCollisionable._height;
    this->_gx = tileCollisionable._gx;
    this->_gy = tileCollisionable._gy;
    return *this;
}