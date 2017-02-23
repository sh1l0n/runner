/**
 * @file   BaseStructure.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class interface
 */

#pragma mark

#include <vector>

namespace Runner {

	/**
	* @short Class BaseStructure, all structures use this parent class
	*/
	class BaseStructure
	{
		protected:

			/** @short Vector of data structure info */
			std::vector<std::vector<unsigned char>> _data;

			/** @short Width of structure */
			unsigned char _width;

			/** @short Height of structure */
			unsigned char _height;
		public:

			/** @short Get the width of structure */
		    unsigned char getWidth() const;

		    /** @short Get the height of structure */
		    unsigned char getHeight() const;

		    /** @short Get the data info of structure */
		    std::vector<std::vector<unsigned char>> getData() const;

		    /** @short Print structure info like a matrix */
		    void print() const;
	};
}