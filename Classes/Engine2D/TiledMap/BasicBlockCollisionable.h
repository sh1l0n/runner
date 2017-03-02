/**
 * @file   TileCollisionable.h
 * @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  TileCollisoinable interface
 */

#pragma once
#include "cocos2d.h"
USING_NS_CC;

namespace TileMap {

    /**
     * @brief Class of a collisionable object
     */
    class BasicBlockCollisionable : public Node {

        private:

            /** @short The local position X */
            float _localPosX;

            /** @short The local position Y */
            float _localPosY;

            /** @short The global position X in the world */
            float _globalPosX;

            /** @short The global position Y in the world */
            float _globalPosY;

            /** @short The width of the block */
            float _width;

            /** @short The height of the block */
            float _height;

        public:

            /** @short Constructor */
            BasicBlockCollisionable(const float localX = 0, const float localY = 0, const float width = 0, const float height = 0);

            /** @short Copy constructor */
            BasicBlockCollisionable(const BasicBlockCollisionable& titleCollisionable);

            /** @short Overload operator = */
            TileMap::BasicBlockCollisionable& operator=(const BasicBlockCollisionable& tileCollisionable);

            /** @short Set the global coordinates for the objects */
            void setGlobalBoundingBox(const float posX, const float posY);

            /** @short Get the global bounding box */
            Rect getGlobalBoundingBox() const;
    };
}



