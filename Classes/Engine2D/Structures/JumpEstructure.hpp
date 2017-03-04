//
// Created by Pablo Ramon on 3/3/17.
//



#pragma once

#include "BaseStructure.hpp"

namespace Structures {
    /**
	* @short Class JumpEstructure, create an structure with damage floor and some platforms to jump along it
	*/
    class JumpEstructure: public BaseStructure {
    private:
        /** @short Default height of the structure */
        const static unsigned int K_DEFAULT_HEIGHT = 3;

        /** @short Default width of the structure */
        const static unsigned int K_DEFAULT_WIDTH = 20;

        /** @short Default max value of x jump of the block structure */
        const static unsigned int K_DEFAULT_MAX_X_DISTANCE_BLOCKS = 2;

        /** @short Default max value of y jump of the block structure */
        const static unsigned int K_DEFAULT_MAX_Y_DISTANCE_BLOCKS = 1;

        unsigned int  _maxXDisBlock;
        unsigned int  _maxYDisBlock;




    public:
        /** @short Creates a new jump structure with default values */
        JumpEstructure();

    };
}


