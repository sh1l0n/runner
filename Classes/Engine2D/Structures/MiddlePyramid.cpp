/**
 * @file   MiddlePyramid.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  MiddlePyramid class implementation
 */

#include "MiddlePyramid.hpp"

/** 
* @brief Creates a middle pyramid structure with a random height
*/
Structures::
MiddlePyramid::MiddlePyramid() : Structures::BaseStructure() 
{
	this->_height = K_DEFAULT_WIDTH;
	this->_width = this->_height;
	this->_data.resize(this->_height);
	unsigned int j, startInRow= this->_height-1;
	this->_vectorCollisionables.resize(this->_height);

	for(int i=_height-1; i>=0; --i) {

		this->_data[i].resize(this->_width, false);
		for(j=startInRow; j<this->_width; ++j) {
			if(j==startInRow || j==this->_width-1){
				this->_data[i][j] = 1;
			}
			else{
				this->_data[i][j] = 5;
			}

		}

		--startInRow;
	}
}
Structures::
MiddlePyramid::MiddlePyramid(unsigned short int width) : Structures::BaseStructure()
{
	this->_height = width;
	this->_width = this->_height;
	this->_data.resize(this->_height);
	unsigned int j, startInRow= this->_height-1;
	this->_vectorCollisionables.resize(this->_height);

	for(int i=_height-1; i>=0; --i) {

		this->_data[i].resize(this->_width, false);
		for(j=startInRow; j<this->_width; ++j) {
			if(j==startInRow || j==this->_width-1){
				this->_data[i][j] = 1;
			}
			else{
				this->_data[i][j] = 5;
			}
		}

		--startInRow;
	}
}