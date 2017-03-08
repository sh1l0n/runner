//
// Created by Pablo Ramon on 3/3/17.
//



#pragma once

#include "BaseStructure.hpp"

namespace Structures {
    /**
	* @short Class JumpEstructure, create an structure with damage floor and some platforms to jump along it
	*/
    class JumpStructure: public BaseStructure {
    private:
        /** @short Default height of the structure */
        const static unsigned short int K_DEFAULT_HEIGHT = 3;

        /** @short Default width of the structure */
        const static unsigned short int K_DEFAULT_WIDTH = 20;

        /** @short Default max value of x jump of the block structure */
        const static unsigned short int K_DEFAULT_MAX_X_DISTANCE_BLOCKS = 2;

        /** @short Default max value of y jump of the block structure */
        const static unsigned short int K_DEFAULT_MAX_Y_DISTANCE_BLOCKS = 1;

        unsigned short int  _maxXDisBlock;
        unsigned short int  _maxYDisBlock;




    public:
        /** @short Creates a new jump structure with default values */
        JumpStructure();
        /** @short Creates a new jump structure with parameters if parameteres are not ok, get default values  */
        JumpStructure(const unsigned short int height, const unsigned  short int width,const unsigned short int max_distanceX,const unsigned short int max_distanceY);

    };
}


