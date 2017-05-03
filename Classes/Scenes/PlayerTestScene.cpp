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
    //const auto size = chunck->_node->getContentSize();
    //log("Add chunck to scene :%d  width: %d, height: %d", id, (int)size.width, (int)size.height);
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
    this->speedM->setPosition(200, 160);
    
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

    this->addChild(parallax, 0);
    this->_nodeScroll= Node::create();
    
    this->addChild(this->_nodeScroll, 1);
    
    this->addChild(this->player, 2);
    this->addChild(this->speedM, 2);
    
    this->runAction(Follow::create(this->player));
    
    //Set map controller
    log("Init map controller");
    this->_mapController = TiledMap::TiledMapController(this);
    
    
    
    m_labelPuntuacion = Label::createWithTTF("Puntuación:", "fonts/Marker Felt.ttf", 24);
    
    
    m_labelPuntuacion->setPosition(Vec2(origin.x + visibleSize.width/2,
                                        origin.y + visibleSize.height - m_labelPuntuacion->getContentSize().height));
    
    m_labelPuntuacion->setString(StringUtils::format("Puntuacion:%d",speedM->getPositionX()));
    this->addChild(m_labelPuntuacion);
    
    
    //Set touch listeners
    EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = CC_CALLBACK_2(PlayerTestScene::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(PlayerTestScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    
    //Finalez and update UI
    this->scheduleUpdate();
    
 
    return true;
}

bool
Scenes::
PlayerTestScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    Entities::Sound::getInstance()->playSound("Audio/jump.wav");
    this->player->onKeyUp();
    return true;
}

void
Scenes::
PlayerTestScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    this->player->onKeyUpRelease();
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
    if(this->player->getPositionY()<= -400){
        log("Entra: %f",this->player->getPositionY());
        Director::getInstance()->pause();
        Entities::Sound::getInstance()->clearSounds();
        Entities::Sound::getInstance()->stopBackground("background.mp3");
        Entities::Sound::getInstance()->clearSounds();
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
    this->_mapController.update(this->player->getPositionX());
}
