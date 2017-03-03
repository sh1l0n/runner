/**
* @file   TileCollisionable.h
* @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
* @date   February, 2017
* @brief  TileCollisoinable interface
*/

#include "BasicBlockCollisionable.hpp"

/**
 * Build an basic block collisionable object. In first time, the global and local positions are the same
 * @param localX the local positon x
 * @param localY the local positon y
 * @param width  the width
 * @param height the height
 */
TiledMap::
BasicBlockCollisionable::BasicBlockCollisionable(const float localX, const float localY, const float width, const float height) : Node() {

    this->_localPosX=localX;
    this->_localPosY=localY;
    this->_width=width;
    this->_height=height;
    this->_globalPosX=localX;
    this->_globalPosY=localY;
}

/**
 * Copy Constructor
 * @param tileCollisionable object for copy
 */
TiledMap::
BasicBlockCollisionable::BasicBlockCollisionable(const BasicBlockCollisionable& tileCollisionable) {

    this->_localPosX= tileCollisionable._localPosX;
    this->_localPosY= tileCollisionable._localPosY;
    this->_width= tileCollisionable._width;
    this->_height= tileCollisionable._height;
    this->_globalPosX= tileCollisionable._globalPosX;
    this->_globalPosY= tileCollisionable._globalPosY;
}

/**
 * Set global positions. Receive position of the screen and transform the local coordinates to global.
 * @param posX real position x
 * @param posY real position y
 */
void
TiledMap::
BasicBlockCollisionable::setGlobalBoundingBox(const float posX, const float posY) {
    this->_globalPosX=posX+this->_localPosX;
    this->_globalPosY=posY+this->_localPosY;
}

/**
 * Getter
 * @return the bounding box in global world positions
 */
Rect
TiledMap::
BasicBlockCollisionable::getGlobalBoundingBox() const {
    return Rect(this->_globalPosX,this->_globalPosY,this->_width,this->_height);

}

/**
 * Overload operator =
 * @param tileCollisionable object for copy
 * @return object copyied
 */
TiledMap::BasicBlockCollisionable&
TiledMap::
BasicBlockCollisionable::operator=(const TiledMap::BasicBlockCollisionable& tileCollisionable) {
    if(this != &tileCollisionable) {
        *this = TiledMap::BasicBlockCollisionable(tileCollisionable);
    }
    return *this;
}