//
// Created by juancarlos on 26/02/17.
//

#include "PlayerTestScene.hpp"
#include "cocos2d.h"

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

    e = RootEntity::create();
    e->setSprite("CloseNormal.png");
    e->setPosition(32, 200);
    this->addChild(e);

    test = Sprite::create("CloseNormal.png");
    test->setPosition(32, 164);
    this->addChild(test);

    this->scheduleUpdate();
    return true;
}


void PlayerTestScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void PlayerTestScene::update(float delta){
    testX+=1.2;
    test->setPosition(testX, 164);

    e->update(delta);
    e->draw(delta);

}
