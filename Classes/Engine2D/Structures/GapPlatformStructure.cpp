//
//  GapPlatformStructure.cpp
//  Runner
//
//  Created by Pablo Ramon on 2/5/17.
//
//

#include "GapPlatformStructure.hpp"


/**
 * @brief Creates a jump structure with default values
 */
Structures::
GapPlatformStructure::GapPlatformStructure() : Structures::BaseStructure()
{
    
    this->_height =K_DEFAULT_HEIGHT;
    this->_width = K_DEFAULT_WIDTH;
    this->_maxXDisBlock=K_DEFAULT_MAX_X_DISTANCE_BLOCKS;
    this->_maxYDisBlock=K_DEFAULT_MAX_Y_DISTANCE_BLOCKS;
    
    
    this->_data.resize(this->_height);
    int i=0,posX,posY;
    for(i=this->_height-1; i>=0; i--) {
        this->_data[i].resize(this->_width, false);
        
    }
    //spike floor 3,  collisionable block 1, nothing 0
    //spike floor
    for(i=0;i<_width;i++){
        this->_data[0][i]=3;
        
    }
    //wall in the begin of the structure
    this->_data[1][0]=1;
    
    posX=0;
    posY=1;
    //Put blocks to pass the spike zone
    
    while(posX+_maxXDisBlock<_width-1){
        //claculate avialable positions in Y
        int maxSaltoAbajo=posY-_maxYDisBlock, maxSaltoArriba=posY+_maxYDisBlock;
        if(maxSaltoArriba>_height-1){
            maxSaltoArriba=_height-1;
        }
        if(maxSaltoAbajo<1){
            maxSaltoAbajo=1;
        }
        //calculate the new block position in Y
        posY= rand()%(maxSaltoArriba-maxSaltoAbajo + 1) + maxSaltoAbajo;
        //new block position in X
        int salto=rand()%(_maxXDisBlock + 1)+1;
        posX=posX+salto;
        this->_data[posY][posX]=1;
        
        
        
    }
    
    
}

Structures::
GapPlatformStructure::GapPlatformStructure(const unsigned short int height, const unsigned short int width,const unsigned short int max_distanceX,const unsigned short int max_distanceY) : Structures::BaseStructure()
{
    this->_height =height;
    this->_width = width;
    this->_maxXDisBlock=max_distanceX;
    this->_maxYDisBlock=max_distanceY;
    
    
    this->_data.resize(this->_height);
    int i=0,posX,posY;
    for(i=this->_height-1; i>=0; i--) {
        this->_data[i].resize(this->_width, false);
        
    }
    //without floor
    for(i=0;i<_width;i++){
        this->_data[0][i]=7;
        
    }
    //wall in the begin of the structure
    this->_data[1][0]=4;
    
    posX=0;
    posY=1;
    //Put blocks to pass the spike zone
    bool isCoin;
    
    while(posX+_maxXDisBlock<_width-1){
        //claculate avialable positions in Y
        int maxSaltoAbajo=posY-_maxYDisBlock, maxSaltoArriba=posY+_maxYDisBlock;
        if(maxSaltoArriba>_height-1){
            maxSaltoArriba=_height-1;
        }
        if(maxSaltoAbajo<1){
            maxSaltoAbajo=1;
        }
        //calculate the new block position in Y
        posY= rand()%(maxSaltoArriba-maxSaltoAbajo + 1) + maxSaltoAbajo;
        //new block position in X
        int salto=rand()%(_maxXDisBlock + 1)+1;
        posX=posX+salto;
        this->_data[posY][posX]=4;
        if(posY<height-1){
            //is possible put a coin
            int rander = rand()%(2);
            isCoin = (rander==1);
            
            if(isCoin) {
                this->_data[posY+1][posX]=8;
            }
            
        }
        
        
        
    }
    
    
}
