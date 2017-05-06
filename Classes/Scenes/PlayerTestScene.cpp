#include <iostream>

#include "PlayerTestScene.hpp"
#include "../Engine2D/MathHelper.hpp"
#include "../Engine2D/TiledMap/TiledMapGenerator.hpp"
#include "../Entities/Sound.hpp"

USING_NS_CC;

//##############################################################################
//Creation of the scene setting the listener for managing the created one
//##############################################################################

cocos2d::Scene*
Scenes::PlayerTestScene::createScene(Scenes::SceneControllerListener* listener)
{
    cocos2d::Scene* scene = Scene::create();
    auto layer = PlayerTestScene::create();
    layer->setListener(listener);
    scene->addChild(layer);
    return scene;
}

//##############################################################################
//Chunk removed for free memory
//##############################################################################

void
Scenes::
PlayerTestScene::removeChunckFromScene(const TiledMap::ChunckIdentifiers id)
{
    log("Remove chunck from scene :%d", id);
    this->_nodeScroll->removeChildByTag(id, true);
}

//##############################################################################
//Cretes new chunk when the player is in the final of the first one
//##############################################################################

void
Scenes::
PlayerTestScene::addChunckToScene(const TiledMap::ChunckIdentifiers id, TiledMap::Chunck* chunck)
{
    this->_nodeScroll->addChild(chunck->_node, 1, id);
    this->player->setFloorCollision(chunck->_collisionables);
}

//##############################################################################
//Sound on/off when button it's clicked
//##############################################################################

void
Scenes::PlayerTestScene::setAudioButton(){
    
    if(_listener!=NULL){
        audioButton = cocos2d::ui::Button::create("audio_off.png","audio_on.png");
        if(_listener->getMusic()==true){
            Entities::Sound::getInstance()->playBackground("Audio/background.mp3");
        }else{
            Entities::Sound::getInstance()->clearSounds();
            Entities::Sound::getInstance()->stopBackground("background.mp3");
        }
        audioButton->setScale(TiledMap::ConstanDevices::getInstance()->SIZE_BUTTONS,TiledMap::ConstanDevices::getInstance()->SIZE_BUTTONS);
        this->addChild(audioButton,3);
    }
}

//##############################################################################
//Initialization all of the componentes in game (player, map, buttons, labels)
//##############################################################################

bool
Scenes::
PlayerTestScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->player = Player::create();
    this->speedM = SpeedMarker::create();
    
    //Player
    this->player->setPosition(50, 50);
    //Speed Marker
    this->speedM = SpeedMarker::create();
    this->speedM->setPosition(50, visibleSize.height/2.0f);
    //Screen killer
    this->screenK = ScreenKiller::create();
    this->screenK->setPosition(Director::getInstance()->getVisibleOrigin().x-30,Director::getInstance()->getVisibleOrigin().y);
    
    
    //Background
    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");
    Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                 Rect(0, 0, 1024 , 512));
    spriteBg->setScale(1, 1);
    spriteBg->setPosition(0, 0);
    spriteBg->setAnchorPoint(Vec2(0, 0));
    ParallaxNode* parallax = ParallaxNode::create();
    parallax->addChild(spriteBg, 0, Vec2(0.5f,1), Vec2(0,0));
    
    this->addChild(parallax, 0);
    this->_nodeScroll= Node::create();
    this->addChild(this->_nodeScroll, 1);
    this->addChild(this->player, 2);
    this->addChild(this->speedM, 2);
    this->addChild(this->screenK, 2);
    this->runAction(Follow::create(this->speedM));

    createMenuPause();
    this->_mapController = TiledMap::TiledMapController(this);
    
    m_labelPuntuacion = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 24);
    this->m_labelPuntuacion->setString(StringUtils::format("%d",((int)this->speedM->getPositionX())/10));
    this->addChild(m_labelPuntuacion,3);
    this->pauseButton = cocos2d::ui::Button::create("pause.png");
    this->pauseButton->setScale(TiledMap::ConstanDevices::getInstance()->SIZE_BUTTONS/2,TiledMap::ConstanDevices::getInstance()->SIZE_BUTTONS/2);//-
    this->pauseButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                pause = true;
                break;
            default:
                break;
        }
    });
    
    this->addChild(pauseButton,3);
    
    EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = CC_CALLBACK_2(PlayerTestScene::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(PlayerTestScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    this->scheduleUpdate();

    return true;
}

//##############################################################################
//Listener for managing scenes
//##############################################################################

void
Scenes::
PlayerTestScene::setListener(Scenes::SceneControllerListener* listener) {
    this->_listener = listener;
    setAudioButton();
}

//##############################################################################
//When user clicks, the player jumps
//##############################################################################

bool
Scenes::
PlayerTestScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    
    if(!pause && !dead && _listener->getMusic()){
        Entities::Sound::getInstance()->playSound("Audio/jump.wav");
    }
    this->player->onKeyUp();
    
    return true;
}

//##############################################################################
//When user stops jumping, player fall over
//##############################################################################

void
Scenes::
PlayerTestScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    Entities::Sound::getInstance()->stopSound("Audio/jump.wav");
    this->player->onKeyUpRelease();
}

//##############################################################################
//User continues playing from the paused scene
//##############################################################################

void
Scenes::
PlayerTestScene::retryMenuCallback(cocos2d::Ref *sender) {
    pause=false;
    Director::getInstance()->resume();
    Entities::Sound::getInstance()->resumeBackground();
    this->removeChild(menu);
}

//##############################################################################
//Player is dead when fall off the platform
//##############################################################################

void
Scenes::
PlayerTestScene::gameOver(cocos2d::Ref *sender){
    dead=pause=false;
    Director::getInstance()->resume();
    _listener->changeScene(Scenes::ESceneType::GAMEOVER);
    if(this->_listener->getMusic()){
        Entities::Sound::getInstance()->playBackground("Audio/background.mp3");
    }
    //we put in a position >-400 for not entering in pause conditional again, so we can restart
    this->player->setPositionY(200);
}

//##############################################################################
//Return to the main menu
//##############################################################################

void
Scenes::
PlayerTestScene::mainMenu(cocos2d::Ref *sender){
    dead=pause=false;
    _listener->changeScene(Scenes::ESceneType::MAIN_MENU);
}

//##############################################################################
//Update x fps the player movement
//##############################################################################

void
Scenes::
PlayerTestScene::createMenuPause() {
    
    Menu* menu_ui;
    Director::getInstance()->pause();
    Entities::Sound::getInstance()->clearSounds();
    Sprite* menu_background = cocos2d::Sprite::create("menu_background_portrait.png");
    Label* newGameLabel = Label::createWithTTF("New Game", "fonts/Sudbury Basin 3D.ttf", 48);
    Label* closeLabel = Label::createWithTTF("Main Menu", "fonts/Sudbury Basin 3D.ttf", 48);
    MenuItemLabel* newGameItem = MenuItemLabel::create(newGameLabel,CC_CALLBACK_1(PlayerTestScene::gameOver,this));
    MenuItemLabel* closeItem = MenuItemLabel::create(closeLabel, CC_CALLBACK_1(PlayerTestScene::mainMenu, this));
    
    menu = Node::create();
    menu->retain();
    menu_background->setContentSize(Size(visibleSize.width,visibleSize.height));
    menu_background->setPosition(this->speedM->getPosition().x,this->speedM->getPosition().y);
    
    newGameLabel->setTextColor(blackColor);
    
    closeLabel->setTextColor(blackColor);
    
    if(pause){
        Entities::Sound::getInstance()->pauseBackground();
        Label* retryLabel = Label::createWithTTF("Retry", "fonts/Sudbury Basin 3D.ttf", 48);
        retryLabel->setTextColor(blackColor);
        MenuItemLabel* retryItem = MenuItemLabel::create(retryLabel,CC_CALLBACK_1(PlayerTestScene::retryMenuCallback, this));
        menu_ui = Menu::create(retryItem, newGameItem, closeItem, NULL);
        
    }else{
        Entities::Sound::getInstance()->stopBackground("Audio/background.mp3");
        menu_ui = Menu::create(newGameItem, closeItem, NULL);
    }
    
    menu_ui->setPosition(this->speedM->getPosition().x, this->speedM->getPosition().y);
    menu_ui->alignItemsVertically();
    LayerGradient* layer = LayerGradient::create(blackColor, Color4B(0,0,0,0));
    menu->addChild(layer, 0);
    menu->addChild(menu_background, 1);
    menu->addChild(menu_ui, 2);
}



void
Scenes::
PlayerTestScene::update(float delta){
    
    //##############################################################################
    // Update times FIXME: Corregir problema con delta (es muy invariable y ejecuta el update 4 0 5 veces, desestabilizando el movimiento)
    //##############################################################################
    this->deltaCount += 0.032f;
    this->deltaCountForMap+=0.002f;
    
    pauseButton->setPosition(Vec2(this->speedM->getPosition().x+visibleSize.width/2.2,this->speedM->getPosition().y+visibleSize.height/2.5));
    audioButton->setPosition(Vec2(this->speedM->getPosition().x-visibleSize.width/2.2,this->speedM->getPosition().y+visibleSize.height/2.5));
    m_labelPuntuacion->setPosition(Vec2(this->speedM->getPosition().x,
                                        this->speedM->getPosition().y+visibleSize.height/2.5));
    //##############################################################################
    // If player falls down from the platform
    //##############################################################################

    if(this->player->getPositionY()<= -400){
        dead = true;
    }
    //##############################################################################
    // Check if player falled
    //##############################################################################
    if(dead || pause){
        this->addChild(menu, 4);
    }
    
    
    //screen Killer has reach the player
    if(this->player->getPositionX()<this->screenK->getPositionX()){
        // TO DO
        //the player dies
        dead=true;
        this->m_labelPuntuacion->setString(StringUtils::format(" FIN JUEGO Puntuacion:%f",this->speedM->getPositionX()));
        
    }
    
    //PAB
    this->speedM->customupdate(delta);
    this->screenK->customupdate(delta);

    //##############################################################################
    // Control 15 fps for player movement
    //##############################################################################
    if(this->deltaCount >= 0.067f) {
        this->m_labelPuntuacion->setString(StringUtils::format("%d",((int)this->speedM->getPositionX())/10));
        this->player->customupdate(delta);
         //PAB
        //this->speedM->customupdate(delta);
        //this->screenK->customupdate(delta);
        this->stepTime = this->deltaCount;
        
        this->deltaCount = 0.f;
    }

    this->player->customdraw(delta, this->deltaCount, this->stepTime);
    //this->speedM->customdraw(delta, this->deltaCount, this->stepTime);
    this->_mapController.update(this->speedM->getPositionX());
    
    audioButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                
                if(_listener->getMusic()==true){
                    _listener->setMusic(false);
                }else{
                    _listener->setMusic(true);
                }
                this->removeChild(audioButton);
                setAudioButton();
                break;
            default:
                break;

        }
    });
}
