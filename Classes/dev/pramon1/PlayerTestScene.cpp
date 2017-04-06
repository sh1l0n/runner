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

    //the player
    e = Player::create();
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
    m_scroll= Node::create();
    m_scroll->addChild(pn, 0);
    m_scroll->addChild(e, 2);
    m_scroll->addChild(speedM, 2);
    // m_scroll->runAction(Follow::create(speedM));
    m_scroll->runAction(Follow::create(e));


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



    EventListenerTouchOneByOne* eventListener = EventListenerTouchOneByOne::create();
    eventListener->setSwallowTouches(true);
    eventListener->onTouchBegan = CC_CALLBACK_2(PlayerTestScene::onTouchBegan, this);
    eventListener->onTouchEnded = CC_CALLBACK_2(PlayerTestScene::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
    this->scheduleUpdate();
    return true;
}


bool
PlayerTestScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {

    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    if(touch->getLocation().x>=min_width) {
        e->onKeyUp();
    }
    else {
        e->onKeyDown();
    }
    return true;
}

void
PlayerTestScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

    unsigned int min_width =  Director::getInstance()->getVisibleSize().width/2;
    if(touch->getLocation().x>=min_width) {
        e->onKeyUpRelease();
    }
    else {
        e->onKeyDownRelease();
    }
}

void PlayerTestScene::update(float delta){
    deltaCount += 0.016; // FIXME: Corregir problema con delta (es muy invariable y ejecuta el update 4 0 5 veces, desestabilizando el movimiento)
    //para comprobar si hay que generar el mapa lo hacemos cada 100 ciclos
    deltaCountForMap+=0.002;

    int worldForPosition=0;


    //deltaCount += delta;

    //fifteen frames per second
    if(deltaCount >= 0.067f) {
        m_labelPuntuacion->setString(StringUtils::format("Puntuacion:%f",speedM->getPositionX()));
        e->customupdate(delta);
        speedM->customupdate(delta);
        stepTime = deltaCount;

        deltaCount = 0.f;
    }

    if(deltaCountForMap >= 0.2f) {

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
    }



    e->customdraw(delta, deltaCount, stepTime);
    speedM->customdraw(delta, deltaCount, stepTime);
}
