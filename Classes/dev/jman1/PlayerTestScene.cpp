//
// Created by juancarlos on 26/02/17.
//

#include "PlayerTestScene.hpp"
#include <iostream>
#include "cocos2d.h"
#include <string>
#include "Engine2D/TiledMap/TiledMapGenerator.hpp"

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




    TiledMap::Chunck chunk = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1,true,true);
    //this->addChild(chunk._node);
    this->scheduleUpdate();

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
    m_scroll->addChild(test, 2);


    //The map and the player2
    this->addChild(m_scroll);
    m_scroll->runAction(Follow::create(test));


    return true;
}


void PlayerTestScene::menuCloseCallback(cocos2d::Ref* pSender)
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
