//
// Created by juancarlos on 26/02/17.
//

#include "PlayerTestScene.hpp"
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


    this->_posXStartNewChunck = 0;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    this->_player = RootEntity::create();
    this->_player->setSprite("CloseNormal.png");
    this->_player->setPosition(16, 200);
   // this->_chunckVector.resize(2);
    this->_posXStartNewChunck = 0;


    // this->_chunckVector[0] = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1,true,true);
    //this->_chunckVector[1] = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1,true,true);


    Node *m_scroll= Node::create();

    //The backgroung
    auto chunck = TiledMap::TiledMapGenerator::getInstance()->generateNewChunk(1,0);
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
    m_scroll->addChild(chunck._node, 1);
    m_scroll->addChild(this->_player, 2);
    this->runAction(Follow::create(this->_player));
    this->addChild(m_scroll);
    this->scheduleUpdate();
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

  //  test->update(delta);
    //test->draw(delta);
}
