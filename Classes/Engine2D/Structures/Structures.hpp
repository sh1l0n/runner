/**
 * @file   StructuresGenerator.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  This file contains all includes for use Structures
 */

#pragma once

#include "BaseStructure.hpp"
#include "Pyramid.hpp"
#include "JumpStructure.hpp"
#include "MiddlePyramid.hpp"
#include "GapStructure.hpp"
#include "GapPlatformStructure.hpp"

namespace Structures {

	/** @short The number of structures */
	static const unsigned int K_NUMBER_STRUCTURES = 4;

	/** @short The maximum value for pyrami width */
	static const unsigned char K_MAX_PYRAMID_WIDTH = 11;
	/** @short The minimum value for pyrami width */
	static const unsigned char K_MIM_PYRAMID_WIDTH = 3;

	/** @short The maximum value for middle pyrami width */
	static const unsigned char K_MAX_MIDDLE_PYRAMID_WIDTH = 6;
	/** @short The mimimum value for middle pyrami width */
	static const unsigned char K_MIN_MIDDLE_PYRAMID_WIDTH = 3;


	/** @short The maximum width value for jump Structure */
	static const unsigned char K_MAX_JUMP_STRUCT_WIDTH = 20;
	/** @short The minimum width value for jump Structure */
	static const unsigned char K_MIM_JUMP_STRUCT_WIDTH = 4;


	/** @short The maximum height value for jump Structure */
	static const unsigned char K_MAX_JUMP_STRUCT_HEIGHT = 7;

	/** @short The minimom height value for jump Structure */
	static const unsigned char K_MIN_JUMP_STRUCT_HEIGHT = 3;

	/** @short The maximum x jump for jump Structure */
	static const unsigned char K_MAX_X_JUMP_HEIGHT = 3;
	/** @short The maximum y jump for jump Structure */
	static const unsigned char K_MAX_Y_JUMP_HEIGHT = 2;

	/** @short The maximum width value for gap Structure */
	static const unsigned char K_MAX_GAP_STRUCT_WIDTH = 20;
	/** @short The minimum width value for jump Structure */
	static const unsigned char K_MIN_GAP_STRUCT_WIDTH = 4;
	/** @short The maximum jump value for gap Structure */
	static const unsigned char K_MAX_GAP_STRUCT_JUMP = 4;
	/** @short The minimum jump value for jump Structure */
	static const unsigned char K_MIN_GAP_STRUCT_JUMP = 1;
	/** @short The maximum rest value for gap Structure */
	static const unsigned char K_MAX_GAP_STRUCT_REST = 3;
	/** @short The maximun rest value for jump Structure */
	static const unsigned char K_MIN_GAP_STRUCT_REST = 1;
    
    
    /** @short The maximum width value for GapPlataform Structure */
    static const unsigned char K_MAX_GAPPF_STRUCT_WIDTH = 8;
    /** @short The minimum width value for jump Structure */
    static const unsigned char K_MIM_GAPPF_STRUCT_WIDTH = 4;
    
    
    /** @short The maximum height value for jump Structure */
    static const unsigned char K_MAX_GAPPF_STRUCT_HEIGHT = 7;
    
    /** @short The minimom height value for jump Structure */
    static const unsigned char K_MIN_GAPPF_STRUCT_HEIGHT = 3;
    
    /** @short The maximum x jump for jump Structure */
    static const unsigned char K_MAX_X_GAPPF_JUMP_HEIGHT = 3;
    /** @short The maximum y jump for jump Structure */
    static const unsigned char K_MAX_Y_GAPPF_JUMP_HEIGHT = 2;





	/**
		@brief Generate a random structure
		@retval STRUCTURE a new structure
	*/
	static BaseStructure* getStructureMatrix(int availableXSpace)
	{


        //int typeStructure = rand() % (K_NUMBER_STRUCTURES-1 +1) + 1;
        int typeStructure = 4;
        
        
        BaseStructure* structure = NULL;
        unsigned short int max_width;
        unsigned int width;
        switch(typeStructure) {
            case 1: {
                if (availableXSpace < K_MAX_MIDDLE_PYRAMID_WIDTH) {
                    max_width = availableXSpace;
                } else {
                    max_width = K_MAX_MIDDLE_PYRAMID_WIDTH;
                }
                width = rand() % (max_width - Structures::K_MIN_MIDDLE_PYRAMID_WIDTH + 1) +
                Structures::K_MIN_MIDDLE_PYRAMID_WIDTH;
                
                structure = new MiddlePyramid(width);
                break;
            }
                /*case 2: {
                 if (availableXSpace < K_MAX_PYRAMID_WIDTH) {
                 
                 max_width = availableXSpace;
                 } else {
                 max_width = K_MAX_PYRAMID_WIDTH;
                 }
                 width = rand() % (max_width - Structures::K_MIM_PYRAMID_WIDTH + 1) + Structures::K_MIM_PYRAMID_WIDTH;
                 if (width % 2 == 0) {
                 width--;
                 }
                 
                 
                 structure = new Pyramid(width);
                 break;
                 }*/
            case 2: {
                
                if (availableXSpace < K_MAX_JUMP_STRUCT_WIDTH) {
                    
                    max_width = availableXSpace;
                } else {
                    max_width = K_MAX_JUMP_STRUCT_WIDTH;
                }
                
                unsigned int height =
                rand() % (Structures::K_MAX_JUMP_STRUCT_HEIGHT - K_MIN_JUMP_STRUCT_HEIGHT + 1) + 3;
                width = rand() % (max_width - K_MIM_JUMP_STRUCT_WIDTH + 1) + K_MIM_JUMP_STRUCT_WIDTH;
                unsigned int max_x_block = rand() % (K_MAX_X_JUMP_HEIGHT - 1 + 1) + 1;
                unsigned int max_y_block = rand() % (K_MAX_Y_JUMP_HEIGHT - 1 + 1) + 1;
                
                structure = new JumpStructure(height, width, max_x_block, max_y_block);
                //structure = new JumpEstructure();
            }
                break;
            case 3: {
                
                if (availableXSpace < K_MAX_GAP_STRUCT_WIDTH) {
                    
                    max_width = availableXSpace;
                } else {
                    max_width = K_MAX_GAP_STRUCT_WIDTH;
                }
                
                //unsigned int height = rand()%(Structures::K_MAX_JUMP_STRUCT_HEIGHT-K_MIN_JUMP_STRUCT_HEIGHT + 1) +3;
                width = rand() % (max_width - K_MIN_GAP_STRUCT_WIDTH + 1) + K_MIN_GAP_STRUCT_WIDTH;
                
                
                
                structure = new GapStructure(width,K_MAX_GAP_STRUCT_JUMP,K_MIN_GAP_STRUCT_JUMP,K_MAX_GAP_STRUCT_REST,K_MIN_GAP_STRUCT_REST);
                
                
                break;
            }
            case 4: {
                
                if (availableXSpace < K_MAX_GAPPF_STRUCT_WIDTH) {
                    
                    max_width = availableXSpace;
                } else {
                    max_width = K_MAX_GAPPF_STRUCT_WIDTH;
                }
                
                unsigned int height =
                rand() % (Structures::K_MAX_GAPPF_STRUCT_HEIGHT - K_MIN_GAPPF_STRUCT_HEIGHT + 1) + 3;
                width = rand() % (max_width - K_MIM_GAPPF_STRUCT_WIDTH + 1) + K_MIM_GAPPF_STRUCT_WIDTH;
                unsigned int max_x_block = rand() % (K_MAX_X_GAPPF_JUMP_HEIGHT - 1 + 1) + 1;
                unsigned int max_y_block = rand() % (K_MAX_Y_GAPPF_JUMP_HEIGHT - 1 + 1) + 1;
                
                structure = new GapPlatformStructure(height, width, max_x_block, max_y_block);
                //structure = new JumpEstructure();
            }
        }
        return structure;
    }
}
