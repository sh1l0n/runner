/**
* @file   TileCollisionable.h
* @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
* @date   February, 2017
* @brief  TileCollisoinable interface
*/

#include "BasicBlock.hpp"
#include "TiledMapGenerator.hpp"


TiledMap::
BasicBlock::BasicBlock() : DrawNode() {

}

/**
 * Build an basic block collisionable object. In first time, the global and local positions are the same
 * @param localX the local positon x
 * @param localY the local positon y
 * @param width  the width
 * @param height the height
 */
/*TiledMap::
BasicBlock::BasicBlock(const float X, const float Y, const float width, const float height) : DrawNode() {

    this->_posX=X;
    this->_posY=Y;
    this->_width=width;
    this->_height=height;
    this->_rect= Rect(this->_posX,this->_posY,this->_width,this->_height);
    Color4F white(1, 1, 1, 1);
    this->drawRect(_rect.origin, _rect.size, white);
    this->setAnchorPoint(Vec2(0,0));


}*/

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
    this->_rect=Rect(this->_posX,this->_posY,this->_width,this->_height);
}


/**
 * Getter
 * @return the bounding box in global world positions
 */
Rect
TiledMap::
BasicBlock::getBoundingBox() const {
    return _rect;

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
BasicBlock::create(const float X, const float Y, const float width, const float height,const unsigned short int type, const bool debug_mode)
{
    TiledMap::BasicBlock* ret = new (std::nothrow) TiledMap::BasicBlock();
    if (ret && ret->init())
    {
        ret->autorelease();
        ret->_posX=X;
        ret->_posY=Y;
        ret->_width=width;
        ret->_height=height;
        ret->_rect= Rect(ret->_posX,ret->_posY,ret->_width,ret->_height);
        ret->_type=type;
        if(debug_mode==true) {
            Color4F white(1, 1, 1, 1);
            ret->drawRect(ret->_rect.origin, ret->_rect.size, white);
        }
        ret->setAnchorPoint(Vec2(0, 0));



    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}