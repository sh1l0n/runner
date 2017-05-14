/**
* @file   TileCollisionable.h
* @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
* @date   February, 2017
* @brief  TileCollisoinable interface
*/

#include "../../Utils/Constants.h"
#include "BasicBlock.hpp"
#include "TiledMapGenerator.hpp"
#include <iostream>

TiledMap::
BasicBlock::BasicBlock() : Node() {

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
    this->_type = tileCollisionable._type;
    this->_idtag = tileCollisionable._idtag;
    this->_rect=Rect(this->_posX,this->_posY,this->_width,this->_height);
    std::cout<<this->_posX << "//" << this->_posY << "//" << this->_width << "//" << this->_height << std::endl;

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
 *
TiledMap::BasicBlock&
TiledMap::
BasicBlock::operator=(const TiledMap::BasicBlock& tileCollisionable) {
    log("Hello\n");
    if(this != &tileCollisionable) {
        this->_posX= tileCollisionable._posX;
        this->_posY= tileCollisionable._posY;
        this->_width= tileCollisionable._width - tileCollisionable._posX;
        this->_height= tileCollisionable._height - tileCollisionable._posY;
        this->_type = tileCollisionable._type;
        this->_rect.setRect(this->_posX,this->_posY,this->_width,this->_height);
        std::cout<<this->_posX << "pp//" << this->_posY << "//" << this->_width << "//" << this->_height << std::endl;
    }
    return *this;
}*/



/**
 * @brief The creates methods
 * @param X position x
 * @param Y position y
 * @param width witdh
 * @param height heihgt
 * @param type type of block
 * @return a new block
 */
TiledMap::BasicBlock*
TiledMap::
BasicBlock::create(const float X, const float Y, const float width, const float height,const TypeBlock type, int idtag)
{
    TiledMap::BasicBlock* ret = new (std::nothrow) TiledMap::BasicBlock();
    if (ret && ret->init())
    {
        ret->_posX=X;
        ret->_posY=Y;
        ret->_width=width;
        ret->_height=height;
        ret->_rect= Rect(ret->_posX,ret->_posY,ret->_width,ret->_height);
        ret->_type=type;
        ret->_idtag = idtag;
        ret->setAnchorPoint(Vec2(0, 0));
        ret->retain();
    }
    else
    {
        CC_SAFE_DELETE(ret);
    }

    return ret;
}

float
TiledMap::
BasicBlock::getX() const {
    return this->_posX;
}

float
TiledMap::
BasicBlock::getY() const {
    return this->_posY ;
}

float
TiledMap::
BasicBlock::getWidth() const {
    return this->_width - this->_posX;
    //return 70.f;
}

TiledMap::TypeBlock
TiledMap::
BasicBlock::getType() const {
    return _type;
}


float
TiledMap::
BasicBlock::getHeight() const {
    std::cout << "--" << this->_height - this->_posY << std::endl;
    return this->_height - this->_posY;
    //return 70.f;
}

int
TiledMap::
BasicBlock::getIdTag() const{
    return _idtag;
}

void
TiledMap::
BasicBlock::erease() {
    this->_posY = 10000; // I Just can't remove the coin...
}

std::string
TiledMap::
BasicBlock::toString() const {
    std::ostringstream ss;
    ss << "[" << std::to_string(this->_posX) << ", " << this->_posY << ", " << this->_width << ", " << this->_height << "]";
    return ss.str();
}
