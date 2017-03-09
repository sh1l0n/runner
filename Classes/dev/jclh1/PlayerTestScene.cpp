//
// Created by juancarlos on 26/02/17.
//

#include <iostream>

#include "PlayerTestScene.hpp"
#include <Engine2D/MathHelper.hpp>

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
    e->setSprite("CloseNormal.png");
    e->setPosition(32, 200);
    this->addChild(e);

    for(int i = 0; i<10 ; i++) {
        box = RootEntity::create();
        box->setSprite("test/Basepack/Tiles/box.png");
        box->setPosition(70*i, 35);
        box->debug = false;
        this->addChild(box);
        boxes.pushBack(box);
    }

    box = RootEntity::create();
    box->setSprite("test/Basepack/Tiles/box.png");
    box->setPosition(100, 200);
    box->debug = false;
    this->addChild(box);
    boxes.pushBack(box);
    box = RootEntity::create();
    box->setSprite("test/Basepack/Tiles/box.png");
    box->setPosition(350, 105);
    box->debug = false;
    this->addChild(box);
    boxes.pushBack(box);
    box = RootEntity::create();
    box->setSprite("test/Basepack/Tiles/box.png");
    box->setPosition(350, 175);
    box->debug = false;
    this->addChild(box);
    boxes.pushBack(box);

    boxes.pushBack(box);

    e->setFloorCollision(boxes);

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
    if(deltaCount >= 0.067) {
        box->customupdate(delta);
        e->customupdate(delta);
        stepTime = deltaCount;
        deltaCount = 0.f;
    }

    box->customdraw(delta, deltaCount, stepTime);
    e->customdraw(delta, deltaCount, stepTime);
}
