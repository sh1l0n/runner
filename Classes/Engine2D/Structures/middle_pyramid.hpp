/**
 * @file   MiddlePyramid.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  MiddlePyramid class interface
 */

#pragma once


#include "base_structure.hpp"

namespace Structures {

	/**
	* @short Class Middle Pyramid, create an structure like a middle pyramid
	*/
	class MiddlePyramid : public BaseStructure
	{
		private:
			/** @short Maximun height for the middle pyramid */
			const static unsigned char K_MAX_HEIGHT = 0x06;

			/** @short Minimun height for the middle pyramid */
			const static unsigned char K_MIN_HEIGHT = 0x02;

		public:
			/** @short Creates a new middle pyramid structure */
		    MiddlePyramid();
	};
}

