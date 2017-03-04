/**
* @file   TileCollisionable.h
* @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
* @date   February, 2017
* @brief  TiledMapGenerator implementation
*/

#include "TiledMapGenerator.hpp"

#include "../Structures/Structures.hpp"

/**
 * @brief
 */
TiledMap::TiledMapGenerator* TiledMap::TiledMapGenerator::_instance = NULL;


/**
 * Method for get the instance of the clas
 * @return the instance
 */
TiledMap::TiledMapGenerator*
TiledMap::
TiledMapGenerator::getInstance()
{
    if(_instance==NULL) {
        _instance = new TiledMap::TiledMapGenerator();
    }
    return _instance;
}

/**
 * @brief Desconstructor, destroy memory of the instance
 */
TiledMap::
TiledMapGenerator::~TiledMapGenerator() {
    if(this->_instance==NULL) {
       delete this->_instance;
        this->_instance = NULL;
    }
}

/**
 * Generate a new chunk.
 * This method contains and pseudo-random algorithm for generate random chuncks with random structures.
 * @return a new random chunck
 */
TiledMap::T_CHUNK
TiledMap::
TiledMapGenerator::generateNewChunk() const{

    TiledMap::T_CHUNK map;
    map.resize(K_HEIGHT);

    for (unsigned int i = 0; i < K_HEIGHT; ++i) {
        map[i].resize(K_WIDTH, false);

    }

    Structures::BaseStructure *bs = Structures::getStructureMatrix();
    std::string chainStructure = "";
    unsigned int i, j;
    for (i = 0; i < bs->getHeight(); ++i) {
        for (j = 0; j < bs->getWidth(); ++j) {
           // chainStructure += bs->getDataAt(i, j) ? "1 " : "0 ";
            chainStructure +=std::to_string(bs->getDataAt(i, j));
        }
        chainStructure += "\n";
    }
    std::cout << chainStructure;
    std::cout << "\n\n\n\n";

    //Obtenemos la posición relativa para la estrutura en el mapa
    unsigned int startStructureOnOY = K_HEIGHT - K_POSITION_Y_START;
    unsigned int startStructureOnOX = K_POSITION_X_START;
    //unsigned int i,j;

    /*for(i=startStructureOnOY; i<bs->getHeight(); ++i) {
        for(j=startStructureOnOX; j<bs->getWidth(); ++j) {
            map[i][j] = bs->getDataAt(i, j);
        }
    }*/
    unsigned int posicionChunkX, posicionChunkY;

    for (i = 0; i < bs->getHeight(); i++) {
        for (j = 0; j < bs->getWidth(); j++) {
            posicionChunkX = j + startStructureOnOX;
            posicionChunkY = i + startStructureOnOY - 1 - K_HEIGHT_FLOOR;
            map[posicionChunkY][posicionChunkX] = bs->getDataAt(i, j);
        }
    }
    //ponemos el suelo
    int inicioSuelo = K_HEIGHT - 1;
    int finSuelo = K_HEIGHT - K_HEIGHT_FLOOR;
    for (i = inicioSuelo; i >= finSuelo; i--) {
        for (j = 0; j < K_WIDTH; j++) {
            map[i][j] = 2;
        }
    }


    return map;
}


Node*
TiledMap::
TiledMapGenerator::createMapNode(TiledMap::T_CHUNK map) const {

    unsigned int i, j;
    //nodo con el chunk
    Node *nodo = Node::create();

    //esto es temporal, después se añadirá una entidad mapa
    Sprite *sprite = NULL;

    /*  sprite=Sprite::create("CloseNormal.png");
      sprite->setPosition(40,40);
      nodo->addChild(sprite);

      sprite=Sprite::create("CloseNormal.png");
      sprite->setPosition(80,80);
      nodo->addChild(sprite);*/


    for (i = 0; i < TiledMap::K_HEIGHT - 1; i++) {
        for (j = 0; j < TiledMap::K_WIDTH - 1; j++) {
            if (map[i][j] == 1) {
                //TO DO en lugar de un sprtie añadir un nodo Tile de tipo muro, con sus colisiones
                sprite = Sprite::create("CloseNormal.png");
                //esto deberá ser constante por ahora así
                float ancho = sprite->getContentSize().width;
                float alto = sprite->getContentSize().height;
                float posX = j * ancho;
                float posY = (TiledMap::K_HEIGHT - i) * alto;

                sprite->setPosition(Vec2(posX, posY));
                nodo->addChild(sprite);


            }
            if (map[i][j] == 2) {
                //TO DO en lugar de un sprtie añadir un nodo Tile de tipo muro, con sus colisiones
                sprite = Sprite::create("CloseSelected.png");
                //esto deberá ser constante por ahora así
                float ancho = sprite->getContentSize().width;
                float alto = sprite->getContentSize().height;
                float posX = j * ancho;
                float posY = (TiledMap::K_HEIGHT - i) * alto;

                sprite->setPosition(Vec2(posX, posY));
                nodo->addChild(sprite);

            }

        }
    }

    return nodo;

}