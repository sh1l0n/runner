//
// Created by juancarlos on 26/02/17.
//

#include <iostream>

#include "PlayerTestScene.hpp"
#include <Engine2D/MathHelper.hpp>
#include <Engine2D/TiledMap/TiledMapGenerator.hpp>
#include <audio/include/SimpleAudioEngine.h>

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

    e = Player::create();
    // e->setSprite("test/Basepack/player/p1_stand.png");
    e->setPosition(200, 200);

    TiledMap::Chunck chunk = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1, 0);
    Node *m_scroll= Node::create();

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


    m_scroll->addChild(pn, 0);
    m_scroll->addChild(chunk._node, 1);
    m_scroll->addChild(e, 2);
    m_scroll->runAction(Follow::create(e));

    //The map and the player2
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
    //deltaCount += delta;

    //fifteen frames per second
    if(deltaCount >= 0.067f) {
        e->customupdate(delta);
        stepTime = deltaCount;
        deltaCount = 0.f;
    }

    e->customdraw(delta, deltaCount, stepTime);
}