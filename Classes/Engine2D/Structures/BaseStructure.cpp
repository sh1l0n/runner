/**
 * @file   BaseStructure.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class implementation
 */

#include "BaseStructure.hpp"


/** 
*	@brief Getter
*	@retval HEIGHT height of structure
*/
unsigned char 
Runner::
BaseStructure::getHeight() const {
    return this._height;
}

/** 
*	@brief Getter
*	@retval WIDTH width of structure
*/
unsigned char 
Runner::
BaseStructure::getWidth() const {
    return this._width;
}

/** 
*	@brief Print the data structure info
*/
void 
Runner::
BaseStructure::print() const {
	    
}

/** 
*	@brief Getter
*	@retval DATA info structure
*/
std::vector<std::vector<unsigned char>> 
Runner::
BaseStructure::getData() const {
	return this._data;
}
