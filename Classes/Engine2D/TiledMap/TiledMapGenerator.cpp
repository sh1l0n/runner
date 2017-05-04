/**
 * @file   TileCollisionable.h
 * @Author Pablo Ramon, Jesús Manresa Parres (jmp66@alu.ua.es)
 * @date   February, 2017
 * @brief  TiledMapGenerator implementation
 */

#include "TiledMapGenerator.hpp"
#include "../../Utils/Constants.h"
#include "../Structures/Structures.hpp"
#include "cocos2d.h"

/**
 * @brief Instance
 */
TiledMap::TiledMapGenerator* TiledMap::TiledMapGenerator::_instance = NULL;

//INformation about codes of MAP generator
//1-> Block Collisionable RIGID  with sprite wall (Pyramid yan Middle Pyramid Collisionable)
//2->Block Collisionable RIGID whith sprite floor
//3->Block Collisionable  DAMAGE with spike sprite
//4->Block Collisionable RIGID with plataform sprite
//5->Block No Collisionable with sprite  with sprite wall (Py and MIDPY not collisionable)
//6->Clock No Collisionable with sprite floor
TiledMap::
TiledMapGenerator::TiledMapGenerator() {
    this->_mapTextures.reserve(6);
    this->_mapTextures[1] = Director::getInstance()->getTextureCache()->addImage("box.png");
    this->_mapTextures[2] = Director::getInstance()->getTextureCache()->addImage("castleCenter.png");
    this->_mapTextures[3] = Director::getInstance()->getTextureCache()->addImage("liquidLavaTop_mid.png");
    this->_mapTextures[4] = Director::getInstance()->getTextureCache()->addImage("stoneHalf.png");
    this->_mapTextures[5] = this->_mapTextures[1];
    this->_mapTextures[6] = this->_mapTextures[2];
}


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
TiledMap::Chunck
TiledMap::
TiledMapGenerator::generateNewChunk(const unsigned int level, const unsigned long posXInitial) {
    
    //##############################################################################
    //Create auxiliar variables and initialize a few of their
    //##############################################################################
    int i;
    int j;
    int freeSpaceInCurrentChunck;
    unsigned int positionXCurrentChunck;
    unsigned int positionYCurrentChunck;
    unsigned int positionXGeneratedCurrentChunck;
    TiledMap::TypeBlock  basicBlockType;
    unsigned int basicBlockTypeCurrent;
    int rest;
    TiledMap::T_CHUNK mapForTextures;
    TiledMap::Chunck currentChunck;
    Structures::BaseStructure *currentStructure = NULL;
    Sprite *spriteToLoad = NULL;
    Rect rectForBoundingBoxCollisionable;
    TiledMap::BasicBlock *basicBlockCollisionable;
    
    //Pablo________________________________
    //Adaptacion distintos dispositivos
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    std::cout<<" visible origin X:"<<Director::getInstance()->getVisibleOrigin().x;
    
    std::cout<<"visible origin Y:"<<Director::getInstance()->getVisibleOrigin().y;
    std::cout<<"Frame size X:"<<glview->getFrameSize().width;
    std::cout<<"Frame size Y:"<<glview->getFrameSize().height;
    
    
    unsigned int size_image_sprite=ConstanDevices::getInstance()->SIZE_IMAGE_SPRITE;
    float factor_scale= ConstanDevices::getInstance()->FACTOR_SCALE;
    
    
    
    
    //##############################################################################
    //Initialize map for textures to 0's
    //##############################################################################
    mapForTextures.resize(K_WIDTH);
    for (i = 0; i < K_WIDTH; ++i) mapForTextures[i].resize(K_HEIGHT, 0);
    
    
    //##############################################################################
    //If is the first chunck, until position 15 without collisionables in other case in the 4 position
    //##############################################################################
    if (posXInitial == 0) positionXGeneratedCurrentChunck = 15;
    else positionXGeneratedCurrentChunck = 4;
    
    
    //##############################################################################
    //Check in first time the free space avilable
    //##############################################################################
    freeSpaceInCurrentChunck = K_WIDTH - positionXGeneratedCurrentChunck;
    
    //##############################################################################
    //While in the chunck is available free space for include another structure create it
    //in other case finish the chunck
    //##############################################################################
    while (freeSpaceInCurrentChunck > K_MIN_VALUE_FOR_STRUCT) {
        
        //##############################################################################
        //Create a structure and include it in the matrix
        //##############################################################################
        currentStructure = Structures::getStructureMatrix(freeSpaceInCurrentChunck);
        std::cout<<currentStructure->toString();
        
        for (i = 0; i < currentStructure->getWidth(); ++i) {
            for (j = 0; j < currentStructure->getHeight(); ++j) {
                //##############################################################################
                //Update the position of current chucnk and assign this to the current map of textures
                //##############################################################################
                basicBlockTypeCurrent = currentStructure->getDataAt(j, i);
                positionXCurrentChunck = i + positionXGeneratedCurrentChunck;
                positionYCurrentChunck = j + K_HEIGHT_FLOOR;
                mapForTextures[positionXCurrentChunck][positionYCurrentChunck] = basicBlockTypeCurrent;
                basicBlockCollisionable= nullptr;
                
                
                //##############################################################################
                //Check the sprite that will use this position
                //##############################################################################
                switch (basicBlockTypeCurrent) {
                    case 1: //Pyramid and Middle Pyramid
                    case 4: //Lava
                    case 5: //Plataform for Jump Structure
                        basicBlockType = TiledMap::TypeBlock::WALL;
                        break;
                    case 3:
                        basicBlockType = TiledMap::TypeBlock::SPIKE;
                        break;
                    default:
                        basicBlockType = TiledMap::TypeBlock::NONE;
                        /*  std::cout << "sprite not found for guid: "
                         << mapForTextures[positionXCurrentChunck][positionYCurrentChunck] << "\n";
                         */
                        break;
                        
                }
                
                if(basicBlockType != TiledMap::TypeBlock::NONE) {
                    spriteToLoad = Sprite::createWithTexture(this->_mapTextures[basicBlockTypeCurrent],
                                                             Rect(0, 0, size_image_sprite, size_image_sprite));
                    
                    
                    spriteToLoad->setAnchorPoint(Vec2(0, 0));
                    spriteToLoad->setPosition((positionXCurrentChunck * factor_scale * size_image_sprite)+posXInitial,
                                              positionYCurrentChunck * factor_scale * size_image_sprite);
                    spriteToLoad->setScale(factor_scale, factor_scale);
                    
                    currentChunck._node->addChild(spriteToLoad, 0);
                    
                    //##############################################################################
                    //When the sprite is loaded, only now, we have the size of this sprite
                    //and check that is collisionable or not
                    //##############################################################################
                    rectForBoundingBoxCollisionable = spriteToLoad->getBoundingBox();
                    
                    std::cout << "rect for display origin x: " << rectForBoundingBoxCollisionable.origin.x << "\n";
                    
                    
                    switch (basicBlockTypeCurrent) {
                        case 1:
                            rectForBoundingBoxCollisionable = spriteToLoad->getBoundingBox();
                            basicBlockCollisionable = TiledMap::BasicBlock::create(
                                                                                   rectForBoundingBoxCollisionable.origin.x,
                                                                                   rectForBoundingBoxCollisionable.origin.y,
                                                                                   rectForBoundingBoxCollisionable.size.width + rectForBoundingBoxCollisionable.origin.x,
                                                                                   rectForBoundingBoxCollisionable.size.height + rectForBoundingBoxCollisionable.origin.y,
                                                                                   basicBlockType);
                            break;
                            
                        case 3: //Lava for jump Structure, tehe block collisionbale is smaller
                            basicBlockCollisionable = TiledMap::BasicBlock::create(
                                                                                   rectForBoundingBoxCollisionable.origin.x,
                                                                                   rectForBoundingBoxCollisionable.origin.y,
                                                                                   rectForBoundingBoxCollisionable.size.width + rectForBoundingBoxCollisionable.origin.x,
                                                                                   rectForBoundingBoxCollisionable.size.height * 0.65f + rectForBoundingBoxCollisionable.origin.y,
                                                                                   basicBlockType);
                            break;
                        case 4: //Plataform for Jump Structure
                            basicBlockCollisionable = TiledMap::BasicBlock::create(
                                                                                   rectForBoundingBoxCollisionable.origin.x,
                                                                                   rectForBoundingBoxCollisionable.origin.y + 10,
                                                                                   rectForBoundingBoxCollisionable.size.width + rectForBoundingBoxCollisionable.origin.x,
                                                                                   rectForBoundingBoxCollisionable.size.height + rectForBoundingBoxCollisionable.origin.y,
                                                                                   basicBlockType);
                            break;
                            
                        default:
                            basicBlockCollisionable = NULL;
                            /*
                             std::cout << "object with guid: "
                             << mapForTextures[positionXCurrentChunck][positionYCurrentChunck]
                             << " it not collisionable\n";
                             */
                            break;
                    }
                }
                //##############################################################################
                // If the node is collisionable add the object and delete pointer from memory
                //##############################################################################
                if (basicBlockCollisionable != NULL) {
                    currentChunck._node->addChild(basicBlockCollisionable, 1);
                    currentChunck._collisionables.push_back(basicBlockCollisionable);
                }
            }
        }
        
        //##############################################################################
        //Finished the anidates for that included the structure in the map
        //update the positions doing a random rest
        //##############################################################################
        rest = rand() % (K_MAX_VALUE_REST - K_MIN_VALUE_REST + 1) + K_MIN_VALUE_REST;
        positionXGeneratedCurrentChunck += (currentStructure->getWidth() + rest);
        freeSpaceInCurrentChunck -= (currentStructure->getWidth() + rest);
        
        if (currentStructure != NULL) {
            delete currentStructure;
            currentStructure = NULL;
        }
    }
    
    //##############################################################################
    //Generate the floor only in the borders of the map and pick up collisionables
    //##############################################################################
    
    for(i=0; i<K_WIDTH; ++i) {
        for(j=K_HEIGHT_FLOOR-1; j>=0; --j) {
            
            if(j==K_POSITION_FLOOR_COLLISIONABLE && mapForTextures[i][j+1] == 0) {
                mapForTextures[i][j]=2;
            }
            else{
                if(mapForTextures[i][j]!=7){
                    mapForTextures[i][j]=6;
                }
                
            }
            //put 0 for gap Structures
            unsigned int k;
            if(j==K_HEIGHT_FLOOR-1){
                if(mapForTextures[i][j+1]==7){
                    //There is a Gap
                    for(k=0;k<=K_HEIGHT_FLOOR;k++){
                        mapForTextures[i][k]=7;
                    }
                }
            }
            
            //we put the floor sprite if is not 0 (gap)
            if(mapForTextures[i][j]==2 || mapForTextures[i][j]==6){
                spriteToLoad = Sprite::createWithTexture(this->_mapTextures[2],
                                                         Rect(0, 0, size_image_sprite, size_image_sprite));
                spriteToLoad->setScale(factor_scale, factor_scale);
                spriteToLoad->setPosition((i * factor_scale * size_image_sprite)+posXInitial,
                                          j * factor_scale * size_image_sprite);
                spriteToLoad->setAnchorPoint(Vec2(0, 0));
                currentChunck._node->addChild(spriteToLoad, 0);
            }
            
            if(mapForTextures[i][j]==2) {
                Rect rr = spriteToLoad->getBoundingBox();
                auto blockCollisionable = TiledMap::BasicBlock::create(rr.origin.x, rr.origin.y,
                                                                       rr.size.width + rr.origin.x,
                                                                       rr.size.height + rr.origin.y,
                                                                       TiledMap::TypeBlock::FLOOR);
                currentChunck._node->addChild(blockCollisionable, 1);
                currentChunck._collisionables.push_back(blockCollisionable);
            }
            
        }
    }
    
    if(Utils::DEBUG_MODE) {
        std::cout << "Chunck generated correctly " << (int)K_WIDTH << "x" << (int)K_HEIGHT << "\n";
        std::string chainMap = "";
        for(i=TiledMap::K_HEIGHT-1; i>=0; --i) {
            for(j=0; j<TiledMap::K_WIDTH; ++j) {
                chainMap+= std::to_string(mapForTextures[j][i]);
            }
            chainMap +="\n";
            if(i==0)break;
        }
        std::cout<<chainMap;
    }
    
    return currentChunck;
}
