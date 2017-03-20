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
    auto closeItem = MenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            CC_CALLBACK_1(MainMenu::closeMenuCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menuLabel = Label::createWithTTF("Play!", "fonts/Marker Felt.ttf", 24);
    auto playItem = MenuItemLabel::create(menuLabel, CC_CALLBACK_1(MainMenu::playMenuCallback, this));

    auto menu = Menu::create(closeItem, playItem, NULL);

    menu->alignItemsVertically();
    this->addChild(menu, 1);

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

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
    //auto scene = PlayerTestScene::createScene();

    // run
    //director->runWithScene(scene);
}
