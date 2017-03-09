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
//INformation about codes of MAP generator
//1-> Block Collisionable RIGID  with sprite wall (Pyramid yan Middle Pyramid Collisionable)
//2->Block Collisionable RIGID whith sprite floor
//3->Block Collisionable  DAMAGE with spike sprite
//4->Block Collisionable RIGID with plataform sprite
//5->Block No Collisionable with sprite  with sprite wall (Py and MIDPY not collisionable)
//6->Clock No Collisionable with sprite floor



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

/*Node*
TiledMap::
TiledMapGenerator::createMapNode(TiledMap::T_CHUNK map) const {
    //nodo con el tile
    Node *nodo = Node::create();

    Texture2D *texture = Director::getInstance()->getTextureCache()->addImage("box.png");
    Sprite *sprite=Sprite::createWithTexture(texture, Rect(0,0,16,16));
    sprite->setPosition(40,40);
    nodo->addChild(sprite);





    return nodo;

}*/


/**
 * Generate a new chunk.
 * This method contains and pseudo-random algorithm for generate random chuncks with random structures.
 * @return a new random chunck
 */
TiledMap::Chunck
TiledMap::
TiledMapGenerator::generateNewChunk(unsigned short int level,bool isInitial,bool debugMode) const{

    unsigned  int i,j;
    TiledMap::Chunck chunck = TiledMap::Chunck();
    TiledMap::T_CHUNK map;

    map.resize(K_WIDTH);
    for (i = 0; i < K_WIDTH; ++i) {
        map[i].resize(K_HEIGHT, false);

    }




    Texture2D *textureWall = Director::getInstance()->getTextureCache()->addImage("box.png");
    Texture2D *textureFloor = Director::getInstance()->getTextureCache()->addImage("castleCenter.png");
    Texture2D *textureSpike = Director::getInstance()->getTextureCache()->addImage("liquidLavaTop_mid.png");
    Texture2D *texturePlatform = Director::getInstance()->getTextureCache()->addImage("stoneHalf.png");

    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");




    //Generate the map
    //We start to put structures on this position
    unsigned int posicionChunkX, posicionChunkY;
    unsigned int posX_generated=4;
    if(isInitial){
        posX_generated=15;
    }

   short int space_avialable=K_WIDTH-posX_generated;



    //Parse bs to debug map, scene and collisionable vector
    while (space_avialable>K_MIN_VALUE_FOR_STRUCT){
        Structures::BaseStructure *bs = Structures::getStructureMatrix(space_avialable);
        std::cout << bs->toString();
        std::cout << "\n\n\n\n";





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


                // Pyramids and Midle Pyramids
                if(block_type==1 || block_type==5){

                    type_basic_block=TiledMap::BasicBlock::K_TYPE_WALL;

                    //create the node to scene
                    Sprite *sprite=Sprite::createWithTexture(textureWall, Rect(0,0,K_SIZE_IMAGE_SPRITE,K_SIZE_IMAGE_SPRITE));

                    sprite->setScale(K_FACTOR_SCALE,K_FACTOR_SCALE);
                    sprite->setPosition(posicionChunkX*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE,posicionChunkY*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE);
                    sprite->setAnchorPoint(Vec2(0,0));
                    chunck._node->addChild(sprite, 0);

                    if(block_type==1) {
                        //collisionable block
                        Rect rr = sprite->getBoundingBox();
                        auto blockCollisionable = TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y,
                                                                               rr.size.width + rr.origin.x,
                                                                               rr.size.height + rr.origin.y,
                                                                               type_basic_block, debugMode);
                        chunck._node->addChild(blockCollisionable, 1);
                        chunck._collisionables.push_back(*blockCollisionable);
                    }


                }

                //Lava for jump Structure, tehe block collisionbale is smaller
                if(block_type==3){

                    type_basic_block=TiledMap::BasicBlock::K_TYPE_SPIKE;

                    //create the node to scene

                    Sprite *sprite=Sprite::createWithTexture(textureSpike, Rect(0,0,K_SIZE_IMAGE_SPRITE,K_SIZE_IMAGE_SPRITE));
                    sprite->setScale(K_FACTOR_SCALE,K_FACTOR_SCALE);
                    sprite->setPosition(posicionChunkX*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE,posicionChunkY*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE);
                    sprite->setAnchorPoint(Vec2(0,0));
                    chunck._node->addChild(sprite, 0);

                    //collisionable block
                    Rect rr = sprite->getBoundingBox();
                    auto blockCollisionable=TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y, rr.size.width + rr.origin.x, rr.size.height*0.65 + rr.origin.y,
                                                                         type_basic_block,debugMode);

                    chunck._node->addChild(blockCollisionable,1);
                    chunck._collisionables.push_back(*blockCollisionable);
                }

                //Plataform for Jump Structure
                if(block_type==4){

                    type_basic_block=TiledMap::BasicBlock::K_TYPE_WALL;

                    //create the node to scene

                    Sprite *sprite=Sprite::createWithTexture(texturePlatform, Rect(0,0,K_SIZE_IMAGE_SPRITE,K_SIZE_IMAGE_SPRITE));
                    sprite->setScale(K_FACTOR_SCALE,K_FACTOR_SCALE);
                    sprite->setPosition(posicionChunkX*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE,posicionChunkY*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE);
                    sprite->setAnchorPoint(Vec2(0,0));
                    chunck._node->addChild(sprite, 0);

                    //collisionable block
                    Rect rr = sprite->getBoundingBox();
                    auto blockCollisionable=TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y+10, rr.size.width + rr.origin.x, rr.size.height + rr.origin.y,
                                                                         type_basic_block,debugMode);

                    chunck._node->addChild(blockCollisionable,1);
                    chunck._collisionables.push_back(*blockCollisionable);
                }







            }
        }

        posX_generated += bs->getWidth();
        space_avialable -= bs->getWidth();
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


    //put the floor
    unsigned int finSuelo = K_HEIGHT_FLOOR-1;
    for (i = 0; i<K_WIDTH; ++i) {
        for (j =0; j <=finSuelo; ++j) {
            if(j==finSuelo){
                if(map[i][j+1] == 0){
                    map[i][j]=2;
                }
                else{
                    map[i][j]=6;
                }
            }else{
                map[i][j]=6;
            }

            //create the node to scene
            Sprite *sprite=Sprite::createWithTexture(textureFloor, Rect(0,0,K_SIZE_IMAGE_SPRITE,K_SIZE_IMAGE_SPRITE));
            sprite->setScale(K_FACTOR_SCALE,K_FACTOR_SCALE);
            sprite->setPosition(i*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE,j*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE);
            sprite->setAnchorPoint(Vec2(0,0));
            chunck._node->addChild(sprite, 0);

            if(map[i][j]==2) {
                //collisionable block
                Rect rr = sprite->getBoundingBox();
                auto blockCollisionable = TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y,
                                                                       rr.size.width + rr.origin.x,
                                                                       rr.size.height + rr.origin.y,
                                                                       TiledMap::BasicBlock::K_TYPE_FLOOR, debugMode);

                chunck._node->addChild(blockCollisionable, 1);
                chunck._collisionables.push_back(*blockCollisionable);
            }

        }
    }


    //put de background
    int cont=0,pxWidth=K_WIDTH*K_SIZE_IMAGE_SPRITE;

    while(cont<pxWidth){

        Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                     Rect(0, 0, K_SIZE_IMAGE_BG_WIDTH, K_SIZE_IMAGE_BG_HEIGHT));

        spriteBg->setScale(1, 1);
        //spriteBg->setPosition(0,K_HEIGHT_FLOOR*K_FACTOR_SCALE*K_SIZE_IMAGE_SPRITE);
        spriteBg->setPosition(cont, 0);
        spriteBg->setAnchorPoint(Vec2(0, 0));
        chunck._node->addChild(spriteBg, -3);
        cont+=K_SIZE_IMAGE_BG_WIDTH;
        //debug
        cont=pxWidth;

    }





    //debug print the map
    //int k,h;
    chainMap = "";

    for(k=TiledMap::K_HEIGHT-1; k>= 0; --k) {
        for(h=0; h< TiledMap::K_WIDTH; ++h) {
            chainMap+= std::to_string(map[h][k]);
        }
        chainMap +="\n";
    }
    std::cout<<chainMap;





    return chunck;
}
