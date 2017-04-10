//
// Created by chancloid on 12/03/2017.
//
#include "TiledMapController.h"

TiledMap::
TiledMapController::TiledMapController() {
    
}

TiledMap::
TiledMapController::TiledMapController(TiledMapControllerListener* listener) {
    
    
    log("init");
    this->flags.resize(3, false);
    this->_chuncks.reserve(TiledMap::K_NUMBERS_CHUNCKS_MEMORY);
    this->_currentChunck = TiledMap::ChunckIdentifiers::A;
    this->_globalPosition = 0;
    this->_listener = listener;
    this->_chuncks[TiledMap::ChunckIdentifiers::A] = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(0, 0);
    this->_globalPosition += TiledMap::K_WORLD_SIZE_PX;
    this->_indexOfChuncksGenerated = 0;
    this->_chuncks[TiledMap::ChunckIdentifiers::B] = NULL;
    this->_chuncks[TiledMap::ChunckIdentifiers::C] = NULL;
    log("add chunck to scene");
    this->_listener->addChunckToScene(TiledMap::ChunckIdentifiers::A, this->_chuncks[TiledMap::ChunckIdentifiers::A]);

}

TiledMap::
TiledMapController::~TiledMapController()
{
    if (this->_chuncks[TiledMap::ChunckIdentifiers::A] != NULL) {
        delete this->_chuncks[TiledMap::ChunckIdentifiers::A];
        this->_chuncks[TiledMap::ChunckIdentifiers::A] = NULL;
    }
    if (this->_chuncks[TiledMap::ChunckIdentifiers::B] != NULL) {
        delete this->_chuncks[TiledMap::ChunckIdentifiers::B];
        this->_chuncks[TiledMap::ChunckIdentifiers::B] = NULL;
    }
    if (this->_chuncks[TiledMap::ChunckIdentifiers::C] != NULL) {
        delete this->_chuncks[TiledMap::ChunckIdentifiers::C];
        this->_chuncks[TiledMap::ChunckIdentifiers::C] = NULL;
    }
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

    const int localPosition = (K_WORLD_SIZE_PX*this->_indexOfChuncksGenerated);
    log("position!! %d  local: %d chunck number: %d, world size: %d", position, localPosition, this->_indexOfChuncksGenerated, K_WORLD_SIZE_PX);
    
    if(!this->flags[0] && localPosition>=TiledMap::K_FLAG_CHUNCK_PART_1 && localPosition<TiledMap::K_FLAG_CHUNCK_PART_2)
    {
        TiledMap::ChunckIdentifiers lastState = this->getLastChunck();
        this->_listener->removeChunckFromScene(lastState);
        this->flags[0] = true;

        if (this->_chuncks[lastState] != NULL) {
            delete this->_chuncks[lastState];
            this->_chuncks[lastState] = NULL;
        }
    }
    else if(!this->flags[1] && localPosition>=TiledMap::K_FLAG_CHUNCK_PART_2 && localPosition<TiledMap::K_FLAG_CHUNCK_PART_3)
    {
        TiledMap::ChunckIdentifiers nextState = this->getNextChunck();
        if (this->_chuncks[nextState] != NULL) {
            delete this->_chuncks[nextState];
            this->_chuncks[nextState] = NULL;
        }
        this->_chuncks[nextState] = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(0, this->_globalPosition);
        this->_globalPosition+=TiledMap::K_WORLD_SIZE_PX;
        this->flags[1] = true;
    }
    else if(this->flags[2] && localPosition>=K_FLAG_CHUNCK_PART_3)
    {
        TiledMap::ChunckIdentifiers nextState = this->getNextChunck();
        this->_listener->addChunckToScene(nextState, this->_chuncks[nextState]);
        this->flags[2] = true;
    }
    else if(localPosition<=TiledMap::K_FLAG_CHUNCK_THRESHOLD) {
            this->_currentChunck = this->getNextChunck();
            this->_indexOfChuncksGenerated+=1;
            this->flags[0] = false;
            this->flags[1] = false;
            this->flags[2] = false;
    }
}
