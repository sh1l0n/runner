/**
 * @file   Pyramid.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  Pyramid class interface
 */

#pragma mark

#include "base_structure.hpp"
#include <vector>

namespace Runner {

	/**
	* @short Class Pyramid, create an structure like a pyramid
	*/
	class Pyramid : public BaseStructure
	{
		private:
			/** @short Maximun height for the pyramid */
			const static unsigned char K_MAX_HEIGHT = 0x06;

			/** @short Minimun height for the pyramid */
			const static unsigned char K_MIN_HEIGHT = 0x01;

		public:
			/** @short Creates a new pyramid structure */
		    Pyramid();

		    /** @short Delete structure */
		   ~Pyramid();
	};
}