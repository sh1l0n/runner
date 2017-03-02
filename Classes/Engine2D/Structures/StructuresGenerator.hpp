/**
 * @file   StructuresGenerator.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  This file contains all includes for use Structures
 */

#pragma once

#include "BaseStructure.hpp"
#include "pyramid.hpp"
#include "MiddlePyramid.hpp"

namespace Structures {
	class StructuresGenerator{
	/** @short The number of structures */
	private:
	static const unsigned char K_NUMBER_STRUCTURES = 2;

	/**
		@brief Generate a random structure
		@retval STRUCTURE a new structure
	*/
	public:
	static BaseStructure* getStructureMatrix()
	{
		unsigned int typeStructure =  rand() % K_NUMBER_STRUCTURES + 1;
		BaseStructure* structure = NULL;

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
	};

}
