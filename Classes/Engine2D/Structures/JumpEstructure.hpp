//
// Created by Pablo Ramon on 3/3/17.
//

#ifndef MYGAME_JUMPESTRUCTURE_H
#define MYGAME_JUMPESTRUCTURE_H

#pragma once

#include "BaseStructure.hpp"

namespace Structures {
    /**
	* @short Class JumpEstructure, create an structure with damage floor and some platforms to jump along it
	*/
    class JumpEstructure: public BaseStructure {
    private:
        /** @short Default height of the structure */
        const static unsigned char K_DEFAULT_HEIGHT = 0x03;

        /** @short Default width of the structure */
        const static unsigned char K_DEFAULT_WIDTH = 0x020;

        /** @short Default max value of x jump of the block structure */
        const static unsigned char K_DEFAULT_MAX_X_JUMP = 0x01;

        /** @short Default max value of y jump of the block structure */
        const static unsigned char K_DEFAULT_MAX_Y_JUMP = 0x01;

        unsigned int  _maxXJump;
        unsigned int  _maxYJump;




    public:
        /** @short Creates a new jump structure with default values */
        JumpEstructure();

    };
}

#endif //MYGAME_JUMPESTRUCTURE_H
