/**
 * @file   TileCollisionable.h
 * @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  TiledMapGenerator interface
 */

#pragma once
#include <vector>
#include "cocos2d.h"
USING_NS_CC;

namespace TiledMap {

    /** @short  Custom type for a chunk */
    typedef std::vector<std::vector<int> > T_CHUNK;

    /** @short  Width for a chunk */
    static const unsigned char K_WIDTH = 0xD4; //212

    /** @short  Height for a chunk */
    static const unsigned char K_HEIGHT = 0x20; //32

    /** @short  Height of the floor */
    static const unsigned char K_HEIGHT_FLOOR = 0x02;

    /** @short Position X start*/
    static const unsigned char K_POSITION_X_START = 0x00;

    /** @short Position Y start*/
    static const unsigned char K_POSITION_Y_START = 0x00 + K_HEIGHT_FLOOR;

    /**
    * Singleton class TiledMapGenerator for generate random maps
    */
    class TiledMapGenerator {

        private:
            /** @short instance of tile map generator */
            static TiledMapGenerator* _instance;

            /** @short Constructor */
            inline TiledMapGenerator() {};

        public:
            /** @short Destructor */
            ~TiledMapGenerator();

            /** @short Method for get the instance and access to object methods */
            static TiledMapGenerator* getInstance();

            /** @short Method for generate a new chunk */
            T_CHUNK generateNewChunk() const;

            Node* createMapNode(const T_CHUNK map) const;
    };
}
