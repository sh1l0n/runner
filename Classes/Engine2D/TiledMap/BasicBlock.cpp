/**
* @file   TileCollisionable.h
* @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
* @date   February, 2017
* @brief  TileCollisoinable interface
*/

#include "BasicBlock.hpp"

TiledMap::
BasicBlock::BasicBlock() : Node() {

}

/**
 * Build an basic block collisionable object. In first time, the global and local positions are the same
 * @param localX the local positon x
 * @param localY the local positon y
 * @param width  the width
 * @param height the height
 */
TiledMap::
BasicBlock::BasicBlock(const float X, const float Y, const float width, const float height) : Node() {

    this->_posX=X;
    this->_posY=Y;
    this->_width=width;
    this->_height=height;
}

/**
 * Copy Constructor
 * @param tileCollisionable object for copy
 */
TiledMap::
BasicBlock::BasicBlock(const BasicBlock& tileCollisionable) {

    this->_posX= tileCollisionable._posX;
    this->_posY= tileCollisionable._posY;
    this->_width= tileCollisionable._width;
    this->_height= tileCollisionable._height;
}


/**
 * Getter
 * @return the bounding box in global world positions
 */
Rect
TiledMap::
BasicBlock::getBoundingBox() const {
    return Rect(this->_posX,this->_posY,this->_width,this->_height);

}

/**
 * Overload operator =
 * @param tileCollisionable object for copy
 * @return object copyied
 */
TiledMap::BasicBlock&
TiledMap::
BasicBlock::operator=(const TiledMap::BasicBlock& tileCollisionable) {
    if(this != &tileCollisionable) {
        *this = TiledMap::BasicBlock(tileCollisionable);
    }
    return *this;
}


TiledMap::BasicBlock*
TiledMap::
BasicBlock::create()
{
    TiledMap::BasicBlock* ret = new (std::nothrow) TiledMap::BasicBlock();
    if (ret && ret->init())
    {
        ret->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}