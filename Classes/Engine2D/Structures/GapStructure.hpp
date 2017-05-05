//
// Created by Pablo Ramon on 20/3/17.
//

#pragma once

#include "BaseStructure.hpp"
namespace Structures  {
    class GapStructure : public BaseStructure{
    private:


        /** @short default width for gap structure*/
        const static unsigned short int K_DEFAULT_WIDTH = 6;
        /** @short default max jump for gap structure*/
        const static unsigned short int K_DEFAULT_MAX_JUMP = 3;
        /** @short default min jump for gap structure*/
        const static unsigned short int K_DEFAULT_MIN_JUMP = 2;
        /** @short default max rest for gap structure*/
        const static unsigned short int K_DEFAULT_MAX_REST = 4;
        /** @short default min rest  for gap structure*/
        const static unsigned short int K_DEFAULT_MIN_REST = 3;



    public:
        /** @short Creates a new middle pyramid structure whith default value width*/
        GapStructure();
        /** @short Creates a new middle pyramid structure whith width parameter  */
        GapStructure(unsigned short int p_width,unsigned short int p_max_jump,unsigned short int p_min_jump,unsigned short int p_min_rest,unsigned short int p_max_rest );

    };
}
