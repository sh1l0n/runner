/**
 * @file   Pyramid.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  Pyramid class implementation
 */

#include "pyramid.hpp"
#include <stdlib.h>

/** 
* @brief Creates a pyramid structure with a random height
*/
Structures::
Pyramid::Pyramid() : Structures::BaseStructure()
{
	this->_width = K_DEFAULT_WIDTH;
	this->_height = (this->_width+1)/2;

	this->_data.resize(this->_height);
	unsigned int i,j, left = 0, right = this->_width-1;
	for(i=0; i<this->_height; ++i) {
		this->_data[i].resize(this->_width, false);
		if(left==right) {
			this->_data[i][right] = true;
			break;
		}
		for(j=left; j<=right; ++j) {
			this->_data[i][j] = true;
		}
		++left;
		--right;
	}
}

Structures::
Pyramid::Pyramid(unsigned short int width) : Structures::BaseStructure()
{
	this->_width = width;
	this->_height = (this->_width-1)/2;

	this->_data.resize(this->_height);
	unsigned int i,j, left = 0, right = this->_width-1;
	for(i=0; i<this->_height; ++i) {
		this->_data[i].resize(this->_width, false);
		if(left==right) {
			this->_data[i][right] = true;
			break;
		}
		for(j=left; j<=right; ++j) {
			this->_data[i][j] = true;
		}
		++left;
		--right;
	}
}

