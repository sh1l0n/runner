//
// Created by Master Móviles on 20/03/2017.
//

#include <dev/jclh1/PlayerTestScene.hpp>
#include "MainMenu.hpp"

using namespace cocos2d;

cocos2d::Scene *MainMenu::createScene() {

    auto scene = Scene::create();

    auto layer = MainMenu::create();

    scene->addChild(layer);

    return scene;
}

bool MainMenu::init() {

    if(!Layer::init()){
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    /*auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(MainMenu::closeMenuCallback, this));*/

    auto playLabel = Label::createWithTTF("Play!", "fonts/Marker Felt.ttf", 24);
    auto playItem = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenu::playMenuCallback, this));
    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
    auto closeItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MainMenu::closeMenuCallback, this));

    //closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,origin.y + closeItem->getContentSize().height/2));
    playItem->setPosition(Vec2(-140,-80));
    closeItem->setPosition(Vec2(70,-80));
    auto menu = Menu::create(playItem, closeItem, NULL);

    //menu->alignItemsVertically();
    this->addChild(menu, 3);

    auto label = Label::createWithTTF("Runner", "fonts/Marker Felt.ttf", 36);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 2);

    // add "HelloWorld" splash screen"

    //grass
    auto grassBase = getSubImage(576,360);
    auto grassBase2 = getSubImage(576,288);
    auto grassBase3 = getSubImage(576,288);
    auto grassBase4 = getSubImage(576,288);
    auto grassBase5 = getSubImage(576,288);
    auto grassBase6 = getSubImage(576,216);
    putImagePosition(grassBase,65,0,1);
    putImagePosition(grassBase2,135,0,1);
    putImagePosition(grassBase3,205,0,1);
    putImagePosition(grassBase4,275,0,1);
    putImagePosition(grassBase5,345,0,1);
    putImagePosition(grassBase6,415,0,1);
    //pyramid
    auto box = getSubImage(144,504);
    auto box2 = getSubImage(144,504);
    auto box3 = getSubImage(144,504);
    auto box4 = getSubImage(144,504);
    auto box5 = getSubImage(144,504);
    auto box6 = getSubImage(144,504);
    auto box7 = getSubImage(144,504);
    auto box8 = getSubImage(144,504);
    auto box9 = getSubImage(144,504);
    putImagePosition(box,65,70,1);
    putImagePosition(box2,135,70,1);
    putImagePosition(box3,205,70,1);
    putImagePosition(box4,275,70,1);
    putImagePosition(box5,345,70,1);
    putImagePosition(box6,135,140,1);
    putImagePosition(box7,205,140,1);
    putImagePosition(box8,275,140,1);
    putImagePosition(box9,205,210,1);
    //cactus
    Texture2D *textureSprite = Director::getInstance()->getTextureCache()->addImage("tiles_spritesheet.png");
    auto cactus = Sprite::createWithTexture(textureSprite,Rect(842,720,60,140));
    putImagePosition(cactus,420,105,1);
    //signs
    auto sign = getSubImage(288,432);
    auto sign2 = getSubImage(288,432);
    putImagePosition(sign,100,70,2);
    putImagePosition(sign2,310,70,2);
    //door
    auto doorTop = getSubImage(648,360);
    auto doorMid = getSubImage(648,432);
    putImagePosition(doorTop,205,140,2);
    putImagePosition(doorMid,205,70,2);
    //torch
    auto torch = getSubImage(72,144);
    auto torch2 = getSubImage(72,144);
    putImagePosition(torch,135,140,2);
    putImagePosition(torch2,275,140,2);
    //bridge
    auto bridge = getSubImage(288,720);
    putImagePosition(bridge,350,190,2);

    //player
    auto player = getSubImage(432,360);
    putImagePosition(player,350,212,3);

    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");
    Size sizeTexture = textureBackGround->getContentSize();
    Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                 Rect(0, 0, visibleSize.width , visibleSize.height));
    this->addChild(spriteBg, 0);
    spriteBg->setScale(1, 1);
    spriteBg->setPosition(0, 0);
    spriteBg->setAnchorPoint(Vec2(0, 0));
    ParallaxNode* pn = ParallaxNode::create();
    pn->addChild(spriteBg, 0, Vec2(0.5f,1), Vec2(0,0));

    return true;
}

void MainMenu::closeMenuCallback(cocos2d::Ref *sender) {
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif
}

void MainMenu::playMenuCallback(cocos2d::Ref *sender) {

    Director::getInstance()->replaceScene(TransitionFade::create(1.f, PlayerTestScene::createScene()));
}

Sprite * MainMenu::getSubImage(int x, int y){

    Texture2D *textureSprite = Director::getInstance()->getTextureCache()->addImage("tiles_spritesheet.png");
    auto sprite = Sprite::createWithTexture(textureSprite,Rect(x,y,K_DEFAULT_SIZE_SPRITE,K_DEFAULT_SIZE_SPRITE));

    return sprite;
}

void MainMenu::putImagePosition(Sprite *sprite, int x, int y, int pos) {
    sprite->setPosition(Vec2(x,y));
    this->addChild(sprite, pos);
}
