/**
 * @file   TileCollisionable.h
 * @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  TileCollisoinable interface
 */

#pragma once
#include "cocos2d.h"
USING_NS_CC;

namespace TiledMap {

    enum TypeBlock {
        NONE = 0x00,
        WALL = 0x01,
        FLOOR = 0x02,
        SPIKE = 0x03
    };


    /**
     * @brief Class of a collisionable object
     */
    class BasicBlock : public DrawNode {

        private:


            /** @short The local position X */
            float _posX;

            /** @short The local position Y */
            float _posY;

            /** @short The width of the block */
            float _width;

            /** @short The height of the block */
            float _height;

            /** @short The bounding box of the node */
            Rect _rect;



        public:

            TypeBlock  _type;

             BasicBlock();

            /** @short Copy constructor */
            BasicBlock(const BasicBlock& titleCollisionable);

            static BasicBlock* create(const float X, const float Y, const float width, const float height, const TypeBlock type);

            /** @short Overload operator = */
            TiledMap::BasicBlock& operator=(const BasicBlock& tileCollisionable);

            /** @short Get the global bounding box */
            Rect getBoundingBox() const;
    };
}



