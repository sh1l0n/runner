/**
 * @file   MiddlePyramid.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  MiddlePyramid class implementation
 */

#include "MiddlePyramid.hpp"
#include <stdlib.h>

/** 
* @brief Creates a middle pyramid structure with a random height
*/
Structures::
MiddlePyramid::MiddlePyramid() : Structures::BaseStructure() 
{
	this->_height = rand() % K_MAX_HEIGHT + K_MIN_HEIGHT;
	this->_width = this->_height;
	this->_data.resize(this->_height);
	unsigned int i,j, startInRow= this->_height-1;
	this->_vectorCollisionables.resize(this->_height);

	for(i=0; i<this->_height; ++i) {

		this->_data[i].resize(this->_width, false);
		for(j=startInRow; j<this->_width; ++j) {
			this->_data[i][j] = true;
		}

		this->_vectorCollisionables[i] = TileMap::TileCollisionable();
		--startInRow;
	}
}