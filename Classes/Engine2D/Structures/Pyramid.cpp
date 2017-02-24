/**
 * @file   Pyramid.cpp
 * @Author Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  Pyramid class implementation
 */

#include "pyramid.hpp"
#include <stdlib.h>

/** 
* @brief Creates an pyramid structure with a random height
*/
Runner::
Pyramid::Pyramid():BaseStructure() {
	this->_height = rand() % K_MAX_HEIGHT + K_MIN_HEIGHT;;
	this->_width = (this->_height*2)-1;
	this->_data.resize(this->_height);
	
	unsigned char i,j, left = 0, right = this->_width-1;
	for(i=this->_height-1; i>=0; --i) {
		this->_data[i].resize(this->_width, false);
		if(left==right) {
			this->_data[left][right] = true;
			break;
		}
		for(j=left; j<right; ++j) this->_data[i][j] = true;
		++left;
		--right;
	}
	print();
}

/** 
* @brief Destroy pyramid structure

Runner::
Pyramid::~Pyramid() {
	//
}*/
