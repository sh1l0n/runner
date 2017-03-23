//
// Created by juancarlos on 26/02/17.
//

#include <iostream>

#include "PlayerTestScene.hpp"
#include <Engine2D/MathHelper.hpp>
#include <Engine2D/TiledMap/TiledMapGenerator.hpp>

USING_NS_CC;

Scene* PlayerTestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = PlayerTestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayerTestScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto eventListener = EventListenerKeyboard::create();
    //the player
    e = Player::create();
    e->setSprite("CloseNormal.png");
    e->setPosition(200, 200);
    //speed control
    speedM = SpeedMarker::create();
    speedM->setPosition(200, 160);
    //The backgroung
    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");
    Size sizeTexture = textureBackGround->getContentSize();
    Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                 Rect(0, 0, 1024 , 512));
    spriteBg->setScale(1, 1);
    spriteBg->setPosition(0, 0);
    spriteBg->setAnchorPoint(Vec2(0, 0));
    ParallaxNode* pn = ParallaxNode::create();
    pn->addChild(spriteBg, 0, Vec2(0.5f,1), Vec2(0,0));


    //m_scroll is the main node to do the camera follow
    Node *m_scroll= Node::create();
    m_scroll->addChild(pn, 0);
    m_scroll->addChild(e, 2);
    m_scroll->addChild(speedM, 2);
    m_scroll->runAction(Follow::create(speedM));


    //Initialze Infinite map generator with 2 maps
    TiledMap::Chunck chunk = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 0);
    world1=chunk._node;
    //new chunk
    worldSizePx=TiledMap::K_WIDTH*TiledMap::K_SIZE_IMAGE_SPRITE*TiledMap::K_FACTOR_SCALE;

    numWorld=1;

    chunk = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 1);
    world2=chunk._node;
    world2->setPosition(worldSizePx,0);


    m_scroll->addChild(world1, 1);
    m_scroll->addChild(world2, 1);



    //The map
    this->addChild(m_scroll, 0);
    e->setFloorCollision(chunk._collisionables);


    eventListener->onKeyPressed = CC_CALLBACK_2(PlayerTestScene::onKeyPressed, this);
    eventListener->onKeyReleased = CC_CALLBACK_2(PlayerTestScene::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);

    this->scheduleUpdate();
    return true;
}

void PlayerTestScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            e->onKeyLeft();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            e->onKeyRight();
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            e->onKeyUp();
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            e->onKeyDown();
            break;
    }
}
void PlayerTestScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) {
    switch(keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            e->onKeyLeftRelease();
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            e->onKeyRightRelease();
            break;
        case EventKeyboard::KeyCode ::KEY_UP_ARROW:
            e->onKeyUpRelease();
            break;
        case EventKeyboard::KeyCode ::KEY_DOWN_ARROW:
            e->onKeyDownRelease();
            break;
    }
}


void PlayerTestScene::update(float delta){
    deltaCount += 0.016; // FIXME: Corregir problema con delta (es muy invariable y ejecuta el update 4 0 5 veces, desestabilizando el movimiento)
    //para comprobar si hay que generar el mapa lo hacemos cada 100 ciclos
    deltaCountForMap+=0.002;

    //deltaCount += delta;

    //fifteen frames per second
    if(deltaCount >= 0.067f) {
        e->customupdate(delta);
        speedM->customupdate(delta);
        stepTime = deltaCount;
        deltaCount = 0.f;
    }

    if(deltaCountForMap >= 0.2f) {
        std::cout<<speedM->getPositionX();
        //std::cout<<worldSizePx;
        std::cout<<"\n";
        deltaCountForMap = 0.f;
    }



    e->customdraw(delta, deltaCount, stepTime);
    speedM->customdraw(delta, deltaCount, stepTime);
}
