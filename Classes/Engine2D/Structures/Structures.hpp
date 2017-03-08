/**
 * @file   StructuresGenerator.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  This file contains all includes for use Structures
 */

#pragma once

#include "BaseStructure.hpp"
#include "pyramid.hpp"
#include "JumpStructure.hpp"
#include "MiddlePyramid.hpp"

namespace Structures {

	/** @short The number of structures */
	static const unsigned char K_NUMBER_STRUCTURES = 3;

	/** @short The maximum value for pyrami width */
	static const unsigned char K_MAX_PYRAMID_WIDTH = 11;
	/** @short The minimum value for pyrami width */
	static const unsigned char K_MIM_PYRAMID_WIDTH = 3;

	/** @short The maximum value for middle pyrami width */
	static const unsigned char K_MAX_MIDDLE_PYRAMID_WIDTH = 6;
	/** @short The mimimum value for middle pyrami width */
	static const unsigned char K_MIN_MIDDLE_PYRAMID_WIDTH = 2;


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




	/**
		@brief Generate a random structure
		@retval STRUCTURE a new structure
	*/
	static BaseStructure* getStructureMatrix(int availableXSpace)
	{
		unsigned int typeStructure =  rand() % (K_NUMBER_STRUCTURES-1 +1) + 1;
		//unsigned int typeStructure =2;
		BaseStructure* structure = NULL;
		unsigned short int max_width;
		unsigned short int min_width;
		unsigned int width;
		switch(typeStructure) {
			case 1:
				if(availableXSpace<K_MAX_MIDDLE_PYRAMID_WIDTH){
					max_width=availableXSpace;
				}else{
					max_width=K_MAX_MIDDLE_PYRAMID_WIDTH;
				}
				width=rand() % (max_width-Structures::K_MIN_MIDDLE_PYRAMID_WIDTH +1) +Structures::K_MIN_MIDDLE_PYRAMID_WIDTH ;

				structure = new MiddlePyramid(width);
				break;
			case 2:
				if(availableXSpace<K_MAX_PYRAMID_WIDTH){

					max_width=availableXSpace;
				}else{
					max_width=K_MAX_PYRAMID_WIDTH;
				}
				width=rand() % (max_width-Structures::K_MIM_PYRAMID_WIDTH +1) +Structures::K_MIM_PYRAMID_WIDTH ;
				if(width%2==0){
					width--;
				}


				structure = new Pyramid(width);
				break;
			case 3:
				//min  and max values for this estructure
				//TODO put this values in constants, distance x and y depends of jump distance
				//min height=3 min width=3 min distance x 1 min distance y=1
				//max height=10 max width=60 max distance x 3 max distance y=2
				unsigned int height = rand()%(Structures::K_MAX_JUMP_STRUCT_HEIGHT-K_MIN_JUMP_STRUCT_HEIGHT + 1) +3;
				width = rand()%(K_MAX_JUMP_STRUCT_WIDTH-K_MIM_JUMP_STRUCT_WIDTH + 1) +K_MIM_JUMP_STRUCT_WIDTH;
				unsigned int max_x_block = rand()%(K_MAX_X_JUMP_HEIGHT-1 + 1) +1;
				unsigned int max_y_block = rand()%(K_MAX_Y_JUMP_HEIGHT-1 + 1) +1;

				structure = new JumpStructure(height,width,max_x_block,max_y_block);
				//structure = new JumpEstructure();

			break;
		}
		return structure;
	}
}
