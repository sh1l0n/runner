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

Node*
TiledMap::
TiledMapGenerator::createMapNode(TiledMap::T_CHUNK map) const {
    //nodo con el tile
    Node *nodo = Node::create();

    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("box.png");
    Sprite *sprite=Sprite::createWithTexture(texture, Rect(0,0,16,16));
    sprite->setPosition(40,40);
    nodo->addChild(sprite);





    return nodo;

}


/**
 * Generate a new chunk.
 * This method contains and pseudo-random algorithm for generate random chuncks with random structures.
 * @return a new random chunck
 */
TiledMap::Chunck
TiledMap::
TiledMapGenerator::generateNewChunk() const{

    TiledMap::Chunck chunck = TiledMap::Chunck();
    TiledMap::T_CHUNK map;



    map.resize(K_WIDTH);
    for (unsigned int i = 0; i < K_WIDTH; ++i) {
        map[i].resize(K_HEIGHT, false);

    }

    Structures::BaseStructure *bs = Structures::getStructureMatrix();


    std::cout << bs->toString();
    std::cout << "\n\n\n\n";


    //Obtenemos la posición relativa para la estrutura en el mapa
    unsigned int startStructureOnOY = K_POSITION_Y_START;
    unsigned int startStructureOnOX = K_POSITION_X_START;
    //unsigned int i,j;


    unsigned int posicionChunkX, posicionChunkY,i,j;

    for (i = 0; i < bs->getWidth(); i++) {
        for (j = 0; j < bs->getHeight(); j++) {
            posicionChunkX = i + startStructureOnOX;
            posicionChunkY = j + K_HEIGHT_FLOOR;
            map[posicionChunkX][posicionChunkY] = bs->getDataAt(i, j);
        }
    }
    //ponemos el suelo
    unsigned  int inicioSuelo = 0;
    unsigned int finSuelo = K_HEIGHT_FLOOR-1;
   // TiledMap::BasicBlock *basicBlock = NULL;


    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("box.png");
    //Sprite *sprite=Sprite::createWithTexture(texture, Rect(0,0,16,16));
    //basicBlock = new TiledMap::BasicBlock(i*16, j*16, 16, 16);
    //sprite->setPosition(0*16,0*16);

    //chunck._node->addChild(sprite);



    for (i = 0; i<K_WIDTH; ++i) {
        for (j = inicioSuelo; j <=finSuelo; ++j) {
            map[i][j] = 2;
            //create the node to scene
            Sprite *sprite=Sprite::createWithTexture(texture, Rect(0,0,70,70));
            sprite->setScale(0.5f,0.5f);
            //basicBlock = new TiledMap::BasicBlock(i*16, j*16, 16, 16);
            sprite->setPosition(i*35,j*35);
            sprite->setAnchorPoint(Vec2(0,0));

            chunck._node->addChild(sprite);


        }
    }

   /*for (i = inicioSuelo; i <= finSuelo; i++) {
        for (j = 0; j < K_WIDTH; j++) {
            map[i][j] = 2;
            //create the node to scene
            Sprite *sprite=Sprite::createWithTexture(texture, Rect(0,0,16,16));
            //basicBlock = new TiledMap::BasicBlock(i*16, j*16, 16, 16);
            sprite->setPosition(i*16,j*16);

            chunck._node->addChild(sprite);


        }
    }
    */


    return chunck;
}
