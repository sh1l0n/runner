//
//  ConstantDevices.cpp
//  Runner
//
//  Created by Pablo Ramon on 26/4/17.
//
//

#include "ConstantDevices.hpp"
/**
 * @brief Instance
 */
TiledMap::ConstanDevices* TiledMap::ConstanDevices::_instance = NULL;

TiledMap::
ConstanDevices::ConstanDevices() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    std::cout<<"win size X:"<<Director::getInstance()->getWinSize().width;
    std::cout<<"win size Y:"<<Director::getInstance()->getWinSize().height;
    std::cout<<"Frame size X:"<<glview->getFrameSize().width;
    std::cout<<"Frame size Y:"<<glview->getFrameSize().height;
    
    //deafult values
    this->SIZE_IMAGE_SPRITE=0x46; //70;
    this->FACTOR_SCALE= 0.35f;
    this->SIZE_BUTTONS=0.2f;
    
    if(glview->getFrameSize().width>1000){
        //iphone
        /*size_image_sprite=K_SIZE_IMAGE_SPRITE_DESIGN/2;
        factor_scale=0.5;*/
        this->SIZE_IMAGE_SPRITE=0x23; //35;
        this->FACTOR_SCALE= 0.75f;
        this->SIZE_BUTTONS=0.4f;
        this->FACTOR_SCALE_X_PLAYER=0.6f;
        this->FACTOR_SCALE_Y_PLAYER=0.7f;
        
        
    }
    
    if(glview->getFrameSize().width>2000){
        //ipad
       /* size_image_sprite=K_SIZE_IMAGE_SPRITE_DESIGN/4;
        factor_scale=0.5;*/
        this->SIZE_IMAGE_SPRITE=0x11; //17;
        this->FACTOR_SCALE= 1.0f;
        this->SIZE_BUTTONS=0.8f;
        this->FACTOR_SCALE_X_PLAYER=1.0f;
        this->FACTOR_SCALE_Y_PLAYER=0.9f;
        
    }
    
    
}
/**
 * Method for get the instance of the clas
 * @return the instance
 */
TiledMap::ConstanDevices*
TiledMap::
ConstanDevices::getInstance()
{
    if(_instance==NULL) {
        _instance = new TiledMap::ConstanDevices();
    }
    return _instance;
}

/**
 * @brief Desconstructor, destroy memory of the instance
 */
TiledMap::
ConstanDevices::~ConstanDevices() {
    if(this->_instance==NULL) {
        delete this->_instance;
        this->_instance = NULL;
    }
}

