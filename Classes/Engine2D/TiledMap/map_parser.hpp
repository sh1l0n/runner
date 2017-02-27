//
// Created by chancloid on 27/02/2017.
//

#pragma once
#include <vector>
#include "../Structures/structures.hpp"

namespace TiledMap {

    typedef std::vector< std::vector<bool> > T_CHUNK;

    static const unsigned char K_WIDTH = 212;
    static const unsigned char K_HEIGHT = 32;
    static const unsigned char K_HEIGHT_FLOOR = 0x02;
    static const unsigned char K_POSITION_X_START = 0x00;
    static const unsigned char K_POSITION_Y_START = K_HEIGHT - K_HEIGHT_FLOOR;

    static T_CHUNK generateNewChunck() {

        T_CHUNK map;
        map.resize(K_HEIGHT);

        for(unsigned int i=0; i<K_HEIGHT; ++i) {
            map[i].resize(K_WIDTH, false);

        }

        Structures::BaseStructure* bs = Structures::getStructureMatrix();

        //Obtenemos la posición relativa para la estrutura en el mapa
        unsigned int startStructureOnOY = K_POSITION_Y_START - bs->getHeight();
        unsigned int startStructureOnOX = K_POSITION_X_START;
        unsigned int i,j;

        for(i=startStructureOnOY; i<bs->getHeight(); ++i) {
            for(j=startStructureOnOX; j<bs->getWidth(); ++j) {
                map[i][j] = bs->getDataAt(i, j);
            }
        }

        return map;
    }
}

