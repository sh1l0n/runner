/**
 * @file   Pyramid.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  Pyramid class interface
 */

#pragma once

#include "BaseStructure.hpp"

namespace Structures {

	/**
	* @short Class Pyramid, create an structure like a pyramid
	*/
	class Pyramid : public BaseStructure
	{
		private:
			/** @short Maximun height for the pyramid */
			const static unsigned short int K_MAX_WIDTH = 11;

			/** @short Minimun height for the pyramid */
			const static unsigned short int K_MIN_WIDTH = 3;

			/** @short Minimun height for the pyramid */
			const static unsigned short int K_DEFAULT_WIDTH = 3;

		public:
			/** @short Creates a new pyramid structure with defualt values */
		    Pyramid();
			/** @short Creates a new pyramid structure with parameter */
			Pyramid(unsigned short int width);
	};
}