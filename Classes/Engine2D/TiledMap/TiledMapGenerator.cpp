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
    auto cache = SpriteFrameCache::getInstance();

    cache->addSpriteFramesWithFile("sprites.plist", "sprites.png");
    //Director::getInstance()->getTextureCache()-



 //   Texture2D *textureFloor = Director::getInstance()->getTextureCache()->addImage("box.png");
    Texture2D *textureWall = Director::getInstance()->getTextureCache()->addImage("castleCenter.png");
    Texture2D *textureSpike = Director::getInstance()->getTextureCache()->addImage("liquidLavaTop_mid.png");



    //ponemos el suelo
    unsigned  int inicioSuelo = 0,i,j;
    unsigned int finSuelo = K_HEIGHT_FLOOR-1;
    for (i = 0; i<K_WIDTH; ++i) {
        for (j = inicioSuelo; j <=finSuelo; ++j) {

            map[i][j] = 2;

            //create the node to scene
            Sprite *sprite = Sprite::createWithSpriteFrameName("box.png");
            //Sprite *sprite=Sprite::createWithTexture(textureFloor, Rect(0,0,70,70));
            sprite->setScale(0.5f,0.5f);
            sprite->setPosition(i*35,j*35);
            sprite->setAnchorPoint(Vec2(0,0));
            chunck._node->addChild(sprite, 0);

            //collisionable block
            Rect rr = sprite->getBoundingBox();
            auto blockCollisionable=TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y, rr.size.width + rr.origin.x, rr.size.height + rr.origin.y,
                TiledMap::BasicBlock::K_TYPE_FLOOR);

            chunck._node->addChild(blockCollisionable,1);
            chunck._collisionables.push_back(*blockCollisionable);

        }
    }




    unsigned int posicionChunkX, posicionChunkY;
    //Obtenemos la posición relativa para la estrutura en el mapa
    /*   unsigned int startStructureOnOY = K_POSITION_Y_START;
       unsigned int startStructureOnOX = K_POSITION_X_START;
       //unsigned int i,j;


       unsigned int posicionChunkX, posicionChunkY,i,j;

       for (i = 0; i < bs->getWidth(); i++) {
           for (j = 0; j < bs->getHeight(); j++) {
               posicionChunkX = i + startStructureOnOX;
               posicionChunkY = j + K_HEIGHT_FLOOR;
               map[posicionChunkX][posicionChunkY] = bs->getDataAt(i, j);
           }
       }*/

    //Generate the map
    //We start to put structures on this position
    unsigned int posX_generated=4;
    unsigned int space_avialable=K_WIDTH-posX_generated;
    while (space_avialable>K_MIN_VALUE_FOR_STRUCT){
        Structures::BaseStructure *bs = Structures::getStructureMatrix(space_avialable);
        std::cout << bs->toString();
        std::cout << "\n\n\n\n";


        //Parse bs to debug map, scene and collisionable vector
        unsigned short int block_type;
        for (i = 0; i < bs->getWidth(); i++) {
            for (j = 0; j < bs->getHeight(); j++) {
                posicionChunkX = i + posX_generated;
                posicionChunkY = j + K_HEIGHT_FLOOR;
                block_type=bs->getDataAt(j, i);
                //Texture2D *texture;
                unsigned short int type_basic_block;
                //Map for debug
                map[posicionChunkX][posicionChunkY] = block_type;
                //TODO use positionChunkXY to create the node
                if(block_type==1){
                   // texture=textureWall;
                    type_basic_block=TiledMap::BasicBlock::K_TYPE_WALL;

                    //create the node to scene
                    //Sprite *sprite=Sprite::createWithTexture(texture, Rect(0,0,70,70));
                    Sprite *sprite = Sprite::createWithSpriteFrameName("castleCenter.png");
                    sprite->setScale(0.5f,0.5f);
                    sprite->setPosition(posicionChunkX*35,posicionChunkY*35);
                    sprite->setAnchorPoint(Vec2(0,0));
                    chunck._node->addChild(sprite, 0);

                    //collisionable block
                    Rect rr = sprite->getBoundingBox();
                    auto blockCollisionable=TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y, rr.size.width + rr.origin.x, rr.size.height + rr.origin.y,
                                                                         type_basic_block);

                    chunck._node->addChild(blockCollisionable,1);
                    chunck._collisionables.push_back(*blockCollisionable);


                }
                if(block_type==3){

                    type_basic_block=TiledMap::BasicBlock::K_TYPE_SPIKE;

                    //create the node to scene

                    Sprite *sprite = Sprite::createWithSpriteFrameName("liquidLavaTop_mid.png");
                    sprite->setScale(0.5f,0.5f);
                    sprite->setPosition(posicionChunkX*35,posicionChunkY*35);
                    sprite->setAnchorPoint(Vec2(0,0.2));
                    chunck._node->addChild(sprite, 0);

                    //collisionable block
                    Rect rr = sprite->getBoundingBox();
                    auto blockCollisionable=TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y, rr.size.width + rr.origin.x, rr.size.height*0.8 + rr.origin.y,
                                                                         type_basic_block);

                    chunck._node->addChild(blockCollisionable,1);
                    chunck._collisionables.push_back(*blockCollisionable);
                }







            }
        }

        posX_generated=posX_generated+bs->getWidth();
        space_avialable=space_avialable-bs->getWidth();
        //put a rest
        unsigned short int rest=rand()%(K_MAX_VALUE_REST-K_MIN_VALUE_REST + 1) +K_MIN_VALUE_REST;
        posX_generated=posX_generated+rest;
        space_avialable=space_avialable-rest;


    }




    //debug print the map
    int k,h;
    std::string chainMap = "";

    for(k=TiledMap::K_HEIGHT-1; k>= 0; --k) {
        for(h=0; h< TiledMap::K_WIDTH; ++h) {
            chainMap+= std::to_string(map[h][k]);
        }
        chainMap +="\n";
    }
    std::cout<<chainMap;



    return chunck;
}
