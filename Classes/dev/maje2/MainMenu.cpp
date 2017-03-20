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

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(playItem, closeItem, NULL);

    menu->alignItemsVertically();
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Runner", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 2);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("box.png");
    auto sprite2 = Sprite::create("box.png");
    auto sprite3 = Sprite::create("box.png");
    auto sprite4 = Sprite::create("box.png");


    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");
    Size sizeTexture = textureBackGround->getContentSize();
    Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                 Rect(0, 0, 480 , 320));
    this->addChild(spriteBg, 0);
    spriteBg->setScale(1, 1);
    spriteBg->setPosition(0, 0);
    spriteBg->setAnchorPoint(Vec2(0, 0));
    ParallaxNode* pn = ParallaxNode::create();
    pn->addChild(spriteBg, 0, Vec2(0.5f,1), Vec2(0,0));
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 80)); //Down
    sprite2->setPosition(Vec2(visibleSize.width/2 - 80, visibleSize.height/2));  //Left
    sprite3->setPosition(Vec2(visibleSize.width/2 + 80, visibleSize.height/2));//Right
    sprite4->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 - 80));  //Up

    // add the sprite as a child to this layer
    this->addChild(sprite, 1);
    this->addChild(sprite2, 1);
    this->addChild(sprite3, 1);
    this->addChild(sprite4, 1);

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
