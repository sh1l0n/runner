/**
 * @file   BaseStructure.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class implementation
 */

#include "base_structure.hpp"
#include <string>

Runner::
BaseStructure::BaseStructure() {

}

Runner::
BaseStructure::~BaseStructure() {

}

/** 
*	@brief Getter
*	@retval HEIGHT height of structure
*/
unsigned char 
Runner::
BaseStructure::getHeight() const {
    return this->_height;
}

/** 
*	@brief Getter
*	@retval WIDTH width of structure
*/
unsigned char 
Runner::
BaseStructure::getWidth() const {
    return this->_width;
}

/** 
*	@brief Getter
*	@retval DATA info structure
*/
std::vector< std::vector<bool> > 
Runner::
BaseStructure::getData() const {
	return this->_data;
}

/** @brief Get the info of a position in structure 
*	@param [in] row the row in the structure
*	@param [in] column the column in the structure
*	@retval VALUE the value in this position
*/
bool
Runner::
BaseStructure::getDataAt(unsigned char row, unsigned char column) const
{
	if(row>=0 && row<this->_width && column>=0 && column<this->_height) 
		return this->_data[row][column];
	else return false;
}


std::ostream& 
operator<<(std::ostream& os, const Runner::BaseStructure& p)
{
	std::string chain = "Width: " + std::to_string(p.getWidth()) + "\n";
	chain += "Height: " + std::to_string(p.getHeight()) + "\n";
	for(unsigned char i=0;i<p.getWidth();++i) {
		for(unsigned char j=0;j<p.getHeight();++j) {
			chain+= p.getDataAt(i, j)?"1 ":"0 ";
		}
		chain+="\n";
	}
	std::cout << chain << "\n";
  	os << chain;
	return os;
}
