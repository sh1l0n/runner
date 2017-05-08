//
// Created by chancloid on 12/03/2017.
//
#include "TiledMapController.h"

TiledMap::
TiledMapController::TiledMapController() {
    _K_WORLD_SIZE_PX = (int)(K_WIDTH*ConstanDevices::getInstance()->SIZE_IMAGE_SPRITE*ConstanDevices::getInstance()->FACTOR_SCALE);
    
    _K_FLAG_CHUNCK_PART_1 = _K_WORLD_SIZE_PX/4.f;
    
    _K_FLAG_CHUNCK_PART_2 = (2.f*_K_WORLD_SIZE_PX)/4.f;
    
    _K_FLAG_CHUNCK_PART_3 = (3.f*_K_WORLD_SIZE_PX)/4.f;
    
    _K_FLAG_CHUNCK_THRESHOLD = _K_WORLD_SIZE_PX - TiledMap::K_FLAG_CHUNCK_THRESHOLD;
    
}

TiledMap::
TiledMapController::TiledMapController(TiledMapControllerListener* listener) {
    _K_WORLD_SIZE_PX = (int)(K_WIDTH*ConstanDevices::getInstance()->SIZE_IMAGE_SPRITE*ConstanDevices::getInstance()->FACTOR_SCALE);
    
    _K_FLAG_CHUNCK_PART_1 = _K_WORLD_SIZE_PX/4.f;
    
    _K_FLAG_CHUNCK_PART_2 = (2.f*_K_WORLD_SIZE_PX)/4.f;
    
    _K_FLAG_CHUNCK_PART_3 = (3.f*_K_WORLD_SIZE_PX)/4.f;
    
    _K_FLAG_CHUNCK_THRESHOLD = _K_WORLD_SIZE_PX - TiledMap::K_FLAG_CHUNCK_THRESHOLD;
    
    this->flags.resize(3, false);
    this->_chuncks.reserve(TiledMap::K_NUMBERS_CHUNCKS_MEMORY);
    this->_currentChunck = TiledMap::ChunckIdentifiers::A;
    this->_globalPosition = 0;
    this->_listener = listener;
    this->_chuncks[TiledMap::ChunckIdentifiers::A] = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(0, 0);
    this->_globalPosition += _K_WORLD_SIZE_PX;
    this->_indexOfChuncksGenerated = 0;
    log("add chunck to scene");
    this->_listener->addChunckToScene(TiledMap::ChunckIdentifiers::A, &this->_chuncks[TiledMap::ChunckIdentifiers::A]);
    
}

TiledMap::
TiledMapController::~TiledMapController()
{
    this->_chuncks.clear();
}

TiledMap::ChunckIdentifiers
TiledMap::
TiledMapController::getLastChunck() const {
    TiledMap::ChunckIdentifiers lastState = TiledMap::ChunckIdentifiers::A;
    switch (this->_currentChunck) {
        case A:
            lastState = TiledMap::ChunckIdentifiers::C;
            break;
        case B:
            lastState = TiledMap::ChunckIdentifiers::A;
            break;
        case C:
            lastState = TiledMap::ChunckIdentifiers::B;
            break;
    }
    return lastState;
}

TiledMap::ChunckIdentifiers
TiledMap::
TiledMapController::getNextChunck() const {
    TiledMap::ChunckIdentifiers nextState = TiledMap::ChunckIdentifiers::A;
    switch (this->_currentChunck) {
        case A:
            nextState = TiledMap::ChunckIdentifiers::B;
            break;
        case B:
            nextState = TiledMap::ChunckIdentifiers::C;
            break;
        case C:
            nextState = TiledMap::ChunckIdentifiers::A;
            break;
    }
    return nextState;
}

void
TiledMap::
TiledMapController::removeChildByTag(const int idtag, const int position) {
    
    const int localPosition = position - (_K_WORLD_SIZE_PX*this->_indexOfChuncksGenerated);
    TiledMap::ChunckIdentifiers state;
    if(localPosition<0) {
        state = this->getLastChunck();
    }
    else {
        state = _currentChunck;
    }
    this->_chuncks[state]._node->removeChildByTag(idtag);
}

/**
 @brief This method it's updated depend the position of the character in the screen.
 The functions is really complex, divides the chunck into four parts, the cuts are like a activators for remove or add to CPU/GPU. Ths parts are the next:
 
 · Chunck: [src, a0, a1, a2, dst]
 · a0    -> Remove last chunck from memory (GPU and CPU)
 · a1    -> Add next chunck to CPU
 · a2    -> Add next chucnk to GPU
 
 It is like a state machine.
 
 @param position The position of the character
 */
void
TiledMap::
TiledMapController::update(const int position) {
    
    const int localPosition = position - (_K_WORLD_SIZE_PX*this->_indexOfChuncksGenerated);
    log("position!! %d  local: %d chunck number: %d, world size: %d", position, localPosition, this->_indexOfChuncksGenerated, _K_WORLD_SIZE_PX);
    
    if(!this->flags[0] && localPosition>=_K_FLAG_CHUNCK_PART_1 && localPosition<_K_FLAG_CHUNCK_PART_2)
    {
        TiledMap::ChunckIdentifiers lastState = this->getLastChunck();
        this->flags[0] = true;
        
        auto its = this->_chuncks.find(lastState);
        if(its!=this->_chuncks.end()) {
            this->_listener->removeChunckFromScene(lastState);
            this->_chuncks.erase(its);
        }
    }
    else if(!this->flags[1] && localPosition>=_K_FLAG_CHUNCK_PART_2 && localPosition<_K_FLAG_CHUNCK_PART_3)
    {
        TiledMap::ChunckIdentifiers nextState = this->getNextChunck();
        
        auto its = this->_chuncks.find(nextState);
        if(its!=this->_chuncks.end()) {
            this->_chuncks.erase(its);
        }
        
        this->_chuncks[nextState] = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(0, this->_globalPosition);
        this->_globalPosition+=_K_WORLD_SIZE_PX;
        this->flags[1] = true;
    }
    else if(!this->flags[2] && localPosition>=_K_FLAG_CHUNCK_PART_3)
    {
        TiledMap::ChunckIdentifiers nextState = this->getNextChunck();
        this->_listener->addChunckToScene(nextState, &this->_chuncks[nextState]);
        this->flags[2] = true;
    }
    else if(this->flags[0] && this->flags[1] && this->flags[2] && localPosition>=_K_FLAG_CHUNCK_THRESHOLD) {
        this->_currentChunck = this->getNextChunck();
        this->_indexOfChuncksGenerated+=1;
        this->flags[0] = false;
        this->flags[1] = false;
        this->flags[2] = false;
    }
}
