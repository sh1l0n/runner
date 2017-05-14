/**
 * @file   MiddlePyramid.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  MiddlePyramid class interface
 */

#pragma once


#include "BaseStructure.hpp"

namespace Structures {

	/**
	* @short Class Middle Pyramid, create an structure like a middle pyramid
	*/
	class MiddlePyramid : public BaseStructure
	{
		private:
			/** @short Maximun height for the middle pyramid */
			const static unsigned short int K_MAX_WIDTH = 6;

			/** @short Minimun height for the middle pyramid */
			const static unsigned short int K_MIN_WIDTH = 3;

			/** @short default for the middle pyramid */
			const static unsigned short int K_DEFAULT_WIDTH = 3;


		public:
			/** @short Creates a new middle pyramid structure whith default value width*/
		    MiddlePyramid();
			/** @short Creates a new middle pyramid structure whith width parameter  */
			MiddlePyramid(unsigned short int width);
	};
}

