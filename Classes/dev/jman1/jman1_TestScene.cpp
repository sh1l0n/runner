//
// Created by juancarlos on 26/02/17.
//


#include "PlayerTestScene.hpp"
#include "cocos2d.h"
#include <string>
#include "../../Engine2D/TiledMap/MapParser.hpp"


USING_NS_CC;

Scene* jman_TestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = jman_TestScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool jman_TestScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    this->scheduleUpdate();

    TiledMap::T_CHUNK chunk = TiledMap::generateNewChunck();

    unsigned int i,j;
    std::string chainMap = "";

    for(i=0; i<TiledMap::K_HEIGHT; ++i) {
        for(j=0; j<TiledMap::K_WIDTH; ++j) {
            chainMap+= chunk[i][j]?"1 ":"0 ";
        }
        chainMap +="\n";
    }







    return true;
}


void jman_TestScene::menuCloseCallback(cocos2d::Ref* pSender)
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

