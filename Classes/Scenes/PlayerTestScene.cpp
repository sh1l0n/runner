#include <iostream>

#include "PlayerTestScene.hpp"
#include "../Engine2D/MathHelper.hpp"
#include "../Engine2D/TiledMap/TiledMapGenerator.hpp"
#include "../Entities/Sound.hpp"

USING_NS_CC;

cocos2d::Scene*
Scenes::PlayerTestScene::createScene(Scenes::SceneControllerListener* listener)
{
    cocos2d::Scene* scene = Scene::create();
    auto layer = PlayerTestScene::create();
    layer->setListener(listener);
    scene->addChild(layer);
    return scene;
}

void
Scenes::
PlayerTestScene::removeChunckFromScene(const TiledMap::ChunckIdentifiers id)
{
    log("Remove chunck from scene :%d", id);
    this->_nodeScroll->removeChildByTag(id, true);
}

void
Scenes::
PlayerTestScene::addChunckToScene(const TiledMap::ChunckIdentifiers id, TiledMap::Chunck* chunck)
{
    const auto size = chunck->_node->getContentSize();
    log("Add chunck to scene :%d  width: %d, height: %d", id, (int)size.width, (int)size.height);
    this->_nodeScroll->addChild(chunck->_node, 1, id);
    this->player->setFloorCollision(chunck->_collisionables);
}

void
Scenes::PlayerTestScene::setAudioButton(){
    
    if(_listener!=NULL){
        audioButton = cocos2d::ui::Button::create("audio_off.png","audio_on.png");
        if(_listener->getMusic()==true){
            //audioButton->loadTextureNormal("audio_off.png");
            Entities::Sound::getInstance()->playBackground("Audio/background.mp3");
        }else{
            //audioButton->loadTextureNormal("audio_on.png");
            Entities::Sound::getInstance()->clearSounds();
            Entities::Sound::getInstance()->stopBackground("background.mp3");
        }
        audioButton->setScale(SIZE_BUTTON*2,SIZE_BUTTON*2);
        audioButton->setPosition(Vec2(SPACE_BUTTON_PADDING,//audioButton->getContentSize().width,
                                      origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
        
        this->addChild(audioButton);
    }
}
// on "init" you need to initialize your instance
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
    this->player->setPosition(200, 50);
    this->speedM = SpeedMarker::create();
    this->speedM->setPosition(200, 60);
    
    //Background
    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");
    Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                 Rect(0, 0, 1024 , 512));
    spriteBg->setScale(1, 1);
    spriteBg->setPosition(0, 0);
    spriteBg->setAnchorPoint(Vec2(0, 0));
    ParallaxNode* parallax = ParallaxNode::create();
    parallax->addChild(spriteBg, 0, Vec2(0.5f,1), Vec2(0,0));
    
    this->_sprite = Sprite::create("box.png");
    this->_sprite->setAnchorPoint(Vec2(0.f, 0.f));
    this->_sprite->setPosition(100.f, 40.f);

    // Set node scroll
    this->_nodeScroll= Node::create();
    this->_nodeScroll->addChild(parallax, 0);
    this->_nodeScroll->addChild(this->player, 2);
    this->_nodeScroll->addChild(this->speedM, 2);
    this->_nodeScroll->runAction(Follow::create(this->player));
    this->addChild(this->_nodeScroll);
    
    //Set map controller
    log("Init map controller");
    this->_mapController = TiledMap::TiledMapController(this);
    
    
    m_labelPuntuacion = Label::createWithTTF("Puntuación:", "fonts/Marker Felt.ttf", 24);
    
    
    m_labelPuntuacion->setPosition(Vec2(origin.x + visibleSize.width/2,
                                        origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
    
    m_labelPuntuacion->setString(StringUtils::format("Puntuacion:%f",speedM->getPositionX()));
    this->addChild(m_labelPuntuacion);
    
    pauseButton = cocos2d::ui::Button::create("pause.png");
    pauseButton->setScale(SIZE_BUTTON,SIZE_BUTTON);//->setContentSize();
    pauseButton->setPosition(Vec2(origin.x + visibleSize.width/1.05,
                             origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
    pauseButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
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
    
    this->addChild(pauseButton);
    
    EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = CC_CALLBACK_2(PlayerTestScene::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(PlayerTestScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    //Finale and update UI
    this->scheduleUpdate();
    
    return true;
}

void
Scenes::
PlayerTestScene::setListener(Scenes::SceneControllerListener* listener) {
    this->_listener = listener;
    setAudioButton();
}

bool
Scenes::
PlayerTestScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    if(touch->getLocation().x>=min_width) {
        if(!pause && !dead && _listener->getMusic()){
            Entities::Sound::getInstance()->playSound("Audio/jump.wav");
        }
        this->player->onKeyUp();
    }
    else {
        // this->player->onKeyDown();
    }
    return true;
}

void
Scenes::
PlayerTestScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    Entities::Sound::getInstance()->stopSound("Audio/jump.wav");
    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    if(touch->getLocation().x>=min_width) {
        this->player->onKeyUpRelease();
    }
    else {
       //  this->player->onKeyDownRelease();
    }
}

/*void
Scenes::
PlayerTestScene::onKeyPausePressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
}*/

void
Scenes::
PlayerTestScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    Vec2 position = this->_sprite->getPosition();
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            log("left");
            position.x-=50;
            this->player->onKeyLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            log("right");
            position.x+=50;
            this->player->onKeyRight();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            this->player->onKeyUp();
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            this->player->onKeyDown();
            break;
        default:
            break;
    }
}
void
Scenes::
PlayerTestScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            this->player->onKeyLeftRelease();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            this->player->onKeyRightRelease();
            break;
        case EventKeyboard::KeyCode ::KEY_UP_ARROW:
            this->player->onKeyUpRelease();
            break;
        case EventKeyboard::KeyCode ::KEY_DOWN_ARROW:
            this->player->onKeyDownRelease();
            break;
        default:
            break;
    }
}

void
Scenes::
PlayerTestScene::retryMenuCallback(cocos2d::Ref *sender) {
    pause=false;
    Director::getInstance()->resume();
    Entities::Sound::getInstance()->resumeBackground();
    this->removeChild(menu);
}

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

void
Scenes::
PlayerTestScene::mainMenu(cocos2d::Ref *sender){
    dead=pause=false;
    _listener->changeScene(Scenes::ESceneType::MAIN_MENU);
}

void
Scenes::
PlayerTestScene::update(float delta){
    
    //##############################################################################
    // Update times FIXME: Corregir problema con delta (es muy invariable y ejecuta el update 4 0 5 veces, desestabilizando el movimiento)
    //##############################################################################
    this->deltaCount += 0.016f;
    this->deltaCountForMap+=0.002f;
    
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
        log("Entra: %f",this->player->getPositionY());
        Director::getInstance()->pause();
        Entities::Sound::getInstance()->clearSounds();
        
        newGameLabel = Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 24);
        newGameItem = MenuItemLabel::create(newGameLabel,CC_CALLBACK_1(PlayerTestScene::gameOver,this));
        closeLabel = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);
        closeItem = MenuItemLabel::create(closeLabel, CC_CALLBACK_1(PlayerTestScene::mainMenu, this));
        if(pause){
            retryLabel = Label::createWithTTF("Retry", "fonts/Marker Felt.ttf", 24);
            retryItem = MenuItemLabel::create(retryLabel,CC_CALLBACK_1(PlayerTestScene::retryMenuCallback, this));
            Entities::Sound::getInstance()->pauseBackground();
            menu = Menu::create(retryItem, newGameItem, closeItem, NULL);
            
        }else{
            Entities::Sound::getInstance()->stopBackground("Audio/background.mp3");
            menu = Menu::create(newGameItem, closeItem, NULL);
        }
        menu->setPosition(WINDOWS_SIZE_IPHONE.width/2,origin.y + closeItem->getContentSize().height*2);
        menu->alignItemsVertically();
        this->addChild(menu, 1);
    }

    //##############################################################################
    // Control 15 fps for player movement
    //##############################################################################
    if(this->deltaCount >= 0.067f) {
        this->m_labelPuntuacion->setString(StringUtils::format("Puntuacion:%f",this->speedM->getPositionX()));
        this->player->customupdate(delta);
        this->speedM->customupdate(delta);
        this->stepTime = this->deltaCount;
        this->deltaCount = 0.f;
    }

    this->player->customdraw(delta, this->deltaCount, this->stepTime);
    
    audioButton->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                
                log("TOUCHED AUDIO!");
                if(_listener->getMusic()==true){
                    _listener->setMusic(false);
                }else{
                    _listener->setMusic(true);
                }
                setAudioButton();
                break;
            default:
                break;
        }
    });
}
