//
// Created by Pablo Ramon on 3/3/17.
//

#include "JumpEstructure.hpp"
/**
* @brief Creates a jump structure with default values
*/
Structures::
JumpEstructure::JumpEstructure() : Structures::BaseStructure()
{
    this->_height =K_DEFAULT_HEIGHT-1;
    this->_width = K_DEFAULT_WIDTH-1;
    this->_data.resize(this->_height);

}