/**
 * @file   TileCollisionable.h
 * @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  TiledMapGenerator interface
 */

#pragma once
#include <vector>
#include <unordered_map>
#include "Chunck.h"
#include "ConstantDevices.hpp"
USING_NS_CC;

namespace TiledMap {

    /** @short  Custom type for a chunk */
    typedef std::vector<std::vector<unsigned int> > T_CHUNK;

    /** @short  Width for a chunk */
    static const unsigned char K_WIDTH = 0xD4; //212

    /** @short  Height for a chunk*/
    static const unsigned char K_HEIGHT = 0x10; //16
    

    /** @short  Height of the floor */
    static const unsigned char K_HEIGHT_FLOOR = 0x02;

    /** @short  Position of the floor collsioinable */
    static const unsigned char K_POSITION_FLOOR_COLLISIONABLE = 0x01;

    /** @short Minimum positions free to put  structure:IMPORTANT!!! This Constant must be higher than ALL MIN VALES of structutres */
    static const unsigned char K_MIN_VALUE_FOR_STRUCT = 0x05;

    /** @short Minimum value for REST btween structures*/
    static const unsigned char K_MIN_VALUE_REST = 0x00;

    /** @short Max value for REST btween structures*/
    static const unsigned char K_MAX_VALUE_REST = 0x06;

    /** @short image sprite size*/
    //static const unsigned char K_SIZE_IMAGE_SPRITE = 0x46; //70;
    static const unsigned char K_SIZE_IMAGE_SPRITE_DESIGN = 0x46; //70;
    


    /** @short image sprite scale*/
    //static const float K_FACTOR_SCALE = 0.35f;
    static const float K_FACTOR_SCALE_DESIGN = 0.35f;

    /** @short image background width size*/
    static const unsigned short K_SIZE_IMAGE_BG_WIDTH = 0x0400; //1024

    /** @short image background height size*/
    static const unsigned short K_SIZE_IMAGE_BG_HEIGHTH = 0x0200; //512


    /**
    * Singleton class TiledMapGenerator for generate random maps
    */
    class TiledMapGenerator {

    private:

        /** @short Map of textures */
        std::unordered_map<unsigned int, Texture2D *> _mapTextures;

        /** @short instance of tile map generator */
        static TiledMapGenerator *_instance;

        /** @short Constructor */
        TiledMapGenerator();

    public:
        /** @short Destructor */
        ~TiledMapGenerator();

        /** @short Method for get the instance and access to object methods */
        static TiledMapGenerator *getInstance();

        /** @short Method for generate a new chunk */
        Chunck* generateNewChunk(const unsigned int level, const unsigned long posXInitial);
    };
}
