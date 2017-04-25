#include <iostream>

#include "PlayerTestScene.hpp"
#include "../Engine2D/MathHelper.hpp"
#include "../Engine2D/TiledMap/TiledMapGenerator.hpp"
#include "../Entities/Sound.hpp"

USING_NS_CC;

cocos2d::Scene*
Scenes::PlayerTestScene::createScene()
{
    cocos2d::Scene* scene = Scene::create();
    cocos2d::Layer* layer = PlayerTestScene::create();
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

// on "init" you need to initialize your instance
bool
Scenes::
PlayerTestScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
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
    
    /*m_labelPause = Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 24);
    //m_labelPause->setPosition(Vec2(origin.x + visibleSize.width/1.1,
      //                            origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
    auto pauseItem = MenuItemLabel::create(m_labelPause,NULL);
    pauseItem->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
    auto menu = Menu::create(pauseItem,NULL);
    this->addChild(menu);*/
    auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png", "CloseNormal.png");
    
    //button->setTitleText("Button Text");
    button->setPosition(Vec2(origin.x + visibleSize.width/1.05,
                             origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
    button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                std::cout << "Button 1 clicked" << std::endl;
                pause = true;
                break;
            default:
                break;
        }
    });
    
    this->addChild(button);
    //this->addChild(m_labelPause);
    
    //Set touch listeners
    /*EventListenerKeyboard* eventKeyListener = EventListenerKeyboard::create();
    eventKeyListener->onKeyPressed = CC_CALLBACK_2(PlayerTestScene::onKeyPressed, this);
    eventKeyListener->onKeyReleased = CC_CALLBACK_2(PlayerTestScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventKeyListener, this);*/
    
    EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = CC_CALLBACK_2(PlayerTestScene::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(PlayerTestScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    //Finalez and update UI
    this->scheduleUpdate();
    
    
    
    
    
    
/*
 
    _mapController = TiledMap::TiledMapController(this);
 


    //Initialze Infinite map generator with 2 maps
    chunk1 = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 0);
    world1=chunk1._node;
    //new chunk
    worldSizePx=TiledMap::K_WIDTH*TiledMap::K_SIZE_IMAGE_SPRITE*TiledMap::K_FACTOR_SCALE;

    numWorld=0;

    chunk2 = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 1);
    world2=chunk2._node;
    world2->setPosition(worldSizePx,0);


    m_scroll->addChild(world1, 1);
    m_scroll->addChild(world2, 1);



    //The map
    this->addChild(m_scroll, 0);

    //The GUI its over m_scroll
    m_labelPuntuacion = Label::createWithTTF("Puntuación:", "fonts/Marker Felt.ttf", 24);


    m_labelPuntuacion->setPosition(Vec2(origin.x + visibleSize.width/2,
                                        origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));

    m_labelPuntuacion->setString(StringUtils::format("Puntuacion:%f",speedM->getPositionX()));
    this->addChild(m_labelPuntuacion);

    //we asign chunk1 bwcause world 1 is the active world
    e->setFloorCollision(chunk1._collisionables);
 
 */
    return true;
}

bool
Scenes::
PlayerTestScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    if(touch->getLocation().x>=min_width) {
        Entities::Sound::getInstance()->playSound("Audio/jump.wav");
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
    Director::getInstance()->resume();
    Entities::Sound::getInstance()->resumeBackground();
    this->removeChild(menu);
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
    // Check if player falled
    //##############################################################################
    if(this->player->getPositionY()<= -400 || pause){
        log("Entra: %f",this->player->getPositionY());
        Director::getInstance()->pause();
        Entities::Sound::getInstance()->clearSounds();
        
        if(pause){
            retryLabel = Label::createWithTTF("Retry", "fonts/Marker Felt.ttf", 24);
            retryItem = MenuItemLabel::create(retryLabel,CC_CALLBACK_1(PlayerTestScene::retryMenuCallback, this));//,Director::getInstance()->resume());//CC_CALLBACK_1(Scenes::MainMenuPhone, this));
            Entities::Sound::getInstance()->pauseBackground();
            pause = false;
        }else{
            retryLabel = Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 24);
            retryItem = MenuItemLabel::create(retryLabel,NULL);//,Director::getInstance()->resume());//CC_CALLBACK_1(Scenes::MainMenuPhone, this));
            Entities::Sound::getInstance()->stopBackground("Audio/background.mp3");
        }
        auto closeLabel = Label::createWithTTF("Close", "fonts/Marker Felt.ttf", 24);
        auto closeItem = MenuItemLabel::create(closeLabel, NULL);//CC_CALLBACK_1(, this));
        
        // create menu, it's an autorelease object
        menu = Menu::create(retryItem, closeItem, NULL);
        //menu->setPosition(Vec2::ZERO);
        menu->alignItemsVertically();
        menu->setPosition(WINDOWS_SIZE_IPHONE.width/2,origin.y + closeItem->getContentSize().height);
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
    //this->speedM->customdraw(delta, this->deltaCount, this->stepTime);
    //this->_mapController.update(this->player->getPositionX());
    
    
    //this->player->getPositionX()
    /*if(deltaCountForMap >= 0.2f) {

        //comparamos la posicion del speed con el numero de mundo activo
        //si la posición no corresponde con el mundo activo cambiamos
        worldForPosition=speedM->getPositionX()/worldSizePx;
        if(numWorld<worldForPosition){
            numWorld++;
            std::cout<<"ahora cambiamos al mundo: "+numWorld;
            std::cout<<"\n";
            if(numWorld%2==1){
                //rehacemos el mundo1
                //m_scroll->removeChild(world1,true);
                //world1->release();

                //world1->retain();
                m_scroll->removeChild(world1);
                chunk1 = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 0);
                world1=chunk1._node;
                world1->setPosition(worldSizePx*(numWorld+1),0);

                m_scroll->addChild(world1);

                //ahora cargamos los colisionables del chiunk 2
                e->setFloorCollision(chunk2._collisionables);
                //world1->release();

                //world1->release();
            }
            if(numWorld%2==0){
                //rehacemos el mundo2
                //m_scroll->removeChild(world1,true);
                //world1->release();

                //world1->retain();
                m_scroll->removeChild(world2);
                chunk2 = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 0);
                world2=chunk2._node;
                world2->setPosition(worldSizePx*(numWorld+1),0);

                m_scroll->addChild(world2);
                e->setFloorCollision(chunk1._collisionables);
                //world1->release();

                //world1->release();
            }

        }
        std::cout<<speedM->getPositionX();

        //std::cout<<worldSizePx;
        std::cout<<"\n";
        deltaCountForMap = 0.f;
    }*/
}
