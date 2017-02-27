/**
 * @file   Structures.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  This file contains all includes for use Structures
 */

#pragma once

#include "base_structure.hpp"
#include "pyramid.hpp"
#include "middle_pyramid.hpp"

namespace Structures {

	/** @short The number of structures */
	static const unsigned char K_NUMBER_STRUCTURES = 2;

	/**
		@brief Generate a random structure
		@retval STRUCTURE a new structure
	*/
	BaseStructure* getStructureMatrix()
	{
		unsigned int typeStructure =  rand() % K_NUMBER_STRUCTURES + 1;
		Structures::BaseStructure* structure = NULL;
		
		switch(typeStructure) {
			case 1:
				structure = new Structures::MiddlePyramid();
				break;
			case 2:
				structure = new Structures::Pyramid();
			break;
		}

		return structure;
	}

}
