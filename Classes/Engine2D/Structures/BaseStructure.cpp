/**
 * @file   BaseStructure.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  BaseStructure class implementation
 */

#include "BaseStructure.hpp"

/**
* @brief Constructor of class BaseStructre
*/
Structures::
BaseStructure::BaseStructure() {

}

/**
* @brief Destructor of class BaseStructre
*/
Structures::
BaseStructure::~BaseStructure() {

}

/** 
*	@brief Getter
*	@retval HEIGHT height of structure
*/
unsigned int 
Structures::
BaseStructure::getHeight() const {
    return this->_height;
}

/** 
*	@brief Getter
*	@retval WIDTH width of structure
*/
unsigned int 
Structures::
BaseStructure::getWidth() const {
    return this->_width;
}

/** 
*	@brief Getter
*	@retval DATA info structure
*/
std::vector< std::vector<unsigned int> >
Structures::
BaseStructure::getData() const {
	return this->_data;
}

/** @brief Get the info of a position in structure 
*	@param [in] row the row in the structure
*	@param [in] column the column in the structure
*	@retval VALUE the value in this position
*/
unsigned int
Structures::
BaseStructure::getDataAt(const unsigned int row, const  unsigned int column) const
{
	if(row>=0 && row<this->_height && column>=0 && column<this->_width) 
		return this->_data[row][column];
	else return 0;
}

/**
*	@brief Convert structure to string for debug
*	@retval CHAIN a chain with the info of the structure
*/
std::string
Structures::
BaseStructure::toString() const
{

	std::string chain = "Width: " + std::to_string(this->_width) + "\n";
	chain += "Height: " + std::to_string(this->_height) + "\n";
	//metohod to string print rows in inverse order, from heght to 0
	for(int i=_height-1;i>=0;--i) {
		for(unsigned int j=0;j<this->_width;++j) {
			chain+=std::to_string(this->getDataAt(i, j));
		}
		chain+="\n";
	}
	return chain;
}

std::vector< TiledMap::BasicBlock >
Structures::
BaseStructure::getCollisionableVector() const{
	return this->_vectorCollisionables;
}
