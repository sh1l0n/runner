/**
 * @file   StructuresGenerator.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  This file contains all includes for use Structures
 */

#pragma once

#include "BaseStructure.hpp"
#include "pyramid.hpp"
#include "JumpEstructure.hpp"
#include "MiddlePyramid.hpp"

namespace Structures {

	/** @short The number of structures */
	static const unsigned char K_NUMBER_STRUCTURES = 2;

	/**
		@brief Generate a random structure
		@retval STRUCTURE a new structure
	*/
	static BaseStructure* getStructureMatrix()
	{
		//unsigned int typeStructure =  rand() % K_NUMBER_STRUCTURES + 1;
		unsigned int typeStructure =2;
		BaseStructure* structure = NULL;

		switch(typeStructure) {
			case 1:
				structure = new MiddlePyramid();
				break;
			case 2:
				structure = new Pyramid();
				break;
			case 3:
				//min  and max values for this estructure
				//TODO put this values in constants, distance x and y depends of jump distance
				//min height=3 min width=3 min distance x 1 min distance y=1
				//max height=10 max width=60 max distance x 3 max distance y=2
				unsigned int height = rand()%(10-3 + 1) +3;
				unsigned int width = rand()%(60-15 + 1) +15;
				unsigned int max_x_block = rand()%(3-1 + 1) +1;
				unsigned int max_y_block = rand()%(3-1 + 1) +1;

				structure = new JumpEstructure(height,width,max_x_block,max_y_block);
				//structure = new JumpEstructure();

			break;
		}
		return structure;
	}
}
