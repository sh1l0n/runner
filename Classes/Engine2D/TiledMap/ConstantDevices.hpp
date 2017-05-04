//
//  ConstantDevices.hpp
//  Runner
//
//  Created by Pablo Ramon on 26/4/17.
//
//

#pragma once
#include <vector>
#include <unordered_map>
#include "Chunck.h"
#include <stdio.h>
#include <iostream>
USING_NS_CC;

namespace TiledMap {
    /**
     * Singleton class TiledMapGenerator for generate random maps
     */
    class ConstanDevices {
        
    private:
        
        /** @short Constructor */
        ConstanDevices();
        
    public:
        unsigned char SIZE_IMAGE_SPRITE;
        float SIZE_BUTTONS;
        float FACTOR_SCALE;
        /** @short instance of constant devices */
        static ConstanDevices *_instance;

        
        /** @short Destructor */
        ~ConstanDevices();
        
        /** @short Method for get the instance and access to object methods */
        static ConstanDevices *getInstance();
        
        
    };

}
