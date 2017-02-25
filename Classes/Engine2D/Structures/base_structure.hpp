/**
 * @file   BaseStructure.hpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class interface
 */

#pragma mark

#include <vector>
#include <iostream>

namespace Runner {

	/**
	* @short Class BaseStructure, all structures use this parent class
	*/
	class BaseStructure
	{
		/** @short Make friend overload operator for easy prints */
		friend std::ostream& operator<<(std::ostream&, const BaseStructure&);

		protected:

			/** @short Vector of data structure info */
			std::vector< std::vector<bool> > _data;

			/** @short Width of structure */
			unsigned char _width;

			/** @short Height of structure */
			unsigned char _height;

		public:

			/** @short Creates a new base structure */
		    BaseStructure();

		    /** @short Delete a base structure */
		    ~BaseStructure();

			/** @short Get the width of structure */
		    unsigned char getWidth() const;

		    /** @short Get the height of structure */
		    unsigned char getHeight() const;

		    /** @short Get the data info of structure */
		    std::vector< std::vector<bool> > getData() const;

		    /** @short Get the info of a position in structure */
		    bool getDataAt(unsigned char row, unsigned char column) const;

	};
}