//
//  MainMenuPhone.cpp
//  Runner
//
//  Created by Master Móviles on 22/04/2017.
//
//

#include "MainMenuPhone.hpp"

using namespace cocos2d;

//##############################################################################
//Generate the scene with the main menu
//##############################################################################

cocos2d::Scene*
Scenes::
MainMenuPhone::createScene() {
    
    auto scene = Scene::create();
    
    auto layer = MainMenuPhone::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool
Scenes::
MainMenuPhone::init() {
    
    if(!Layer::init()){
        return false;
    }

    //labels and functionality of the menu. It is on top of all structures with index 4.
    auto playLabel = Label::createWithTTF("Play!", "fonts/Marker Felt.ttf", 24);
    auto playItem = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenuPhone::playMenuCallback, this));
    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
    auto closeItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MainMenuPhone::closeMenuCallback, this));
    closeItem->setPosition(Vec2(-140,-80));
    playItem->setPosition(Vec2(140,-80));
    auto menu = Menu::create(playItem, closeItem, NULL);
    this->addChild(menu, 4);
    
    return true;
}

//##############################################################################
//Stops the game when user click on sign close
//##############################################################################

void
Scenes::
MainMenuPhone::closeMenuCallback(cocos2d::Ref *sender) {
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//##############################################################################
//Starts the game when user click on sign start
//##############################################################################

void
Scenes::
MainMenuPhone::playMenuCallback(cocos2d::Ref *sender) {
    
    /*Entities::Sound::getInstance()->playSound("open_door.mp3");
    
    Entities::Sound::getInstance()->playBackground("background.mp3");
    
    auto doorClosedTop = getSubImage(648,216);
    auto doorClosedMid = getSubImage(648,288);
    putImagePosition(doorClosedTop,205,140,3);
    putImagePosition(doorClosedMid,205,70,3);
    Director::getInstance()->replaceScene(TransitionFade::create(3.f, Scenes::PlayerTestScene::createScene()));*/
}
