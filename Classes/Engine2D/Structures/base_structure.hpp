/**
 * @file   BaseStructure.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class interface
 */

#pragma mark

#include <vector>
#include <iostream>
#include <string>

namespace Runner {

	/**
	* @short Class BaseStructure, all structures use this parent class
	*/
	class BaseStructure
	{
		protected:

			/** @short Vector of data structure info */
			std::vector< std::vector<bool> > _data;

			/** @short Width of structure */
			unsigned int _width;

			/** @short Height of structure */
			unsigned int _height;

		public:

			/** @short Creates a new base structure */
		    BaseStructure();

		    /** @short Delete a base structure */
		    ~BaseStructure();

			/** @short Get the width of structure */
		    unsigned int getWidth() const;

		    /** @short Get the height of structure */
		    unsigned int getHeight() const;

		    /** @short Get the data info of structure */
		    std::vector< std::vector<bool> > getData() const;

		    /** @short Get the info of a position in structure */
		    bool getDataAt(unsigned int row, unsigned int column) const;

			/** @short Convert this class in a string */
			std::string toString() const;
	};
}