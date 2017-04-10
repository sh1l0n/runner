//
// Created by Master Móviles on 20/03/2017.
//

#include "audio/include/SimpleAudioEngine.h"
#include "MainMenu.hpp"
#include "PlayerTestScene.hpp"
#include "../Entities/Sound.hpp"

using namespace cocos2d;

//##############################################################################
//Generate the scene with the main menu
//##############################################################################

cocos2d::Scene*
Scenes::
MainMenu::createScene() {

    auto scene = Scene::create();

    auto layer = MainMenu::create();

    scene->addChild(layer);

    return scene;
}

//##############################################################################
//Generate the menu whose structures and sprites are defined in different layers
//##############################################################################

bool
Scenes::
MainMenu::init() {

    if(!Layer::init()){
        return false;
    }

    //gets the size of the screen
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //labels and functionality of the menu. It is on top of all structures with index 4.
    auto playLabel = Label::createWithTTF("Play!", "fonts/Marker Felt.ttf", 24);
    auto playItem = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenu::playMenuCallback, this));
    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
    auto closeItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MainMenu::closeMenuCallback, this));
    closeItem->setPosition(Vec2(-140,-80));
    playItem->setPosition(Vec2(140,-80));
    auto menu = Menu::create(playItem, closeItem, NULL);
    this->addChild(menu, 4);

    //main tittle
    auto label = Label::createWithTTF("Runner", "fonts/Marker Felt.ttf", 36);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 2);

    //grass base structure
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

    //pyramid structure
    auto box = getSubImage(144,504);
    auto box2 = getSubImage(144,504);
    auto box3 = getSubImage(144,504);
    auto box4 = getSubImage(144,504);
    auto box5 = getSubImage(144,504);
    auto box6 = getSubImage(144,504);
    auto box7 = getSubImage(144,504);
    auto box8 = getSubImage(144,504);
    auto box9 = getSubImage(144,504);
    auto box10 = getSubImage(288,72);
    auto box11 = getSubImage(288,72);
    auto box12 = getSubImage(288,72);
    auto box13 = getSubImage(288,72);
    auto box14 = getSubImage(288,72);
    auto box15 = getSubImage(288,72);
    auto box16 = getSubImage(288,72);
    auto box17 = getSubImage(288,72);
    auto box18 = getSubImage(288,72);
    putImagePosition(box,65,70,2);
    putImagePosition(box2,135,70,2);
    putImagePosition(box3,205,70,2);
    putImagePosition(box4,275,70,2);
    putImagePosition(box5,345,70,2);
    putImagePosition(box6,135,140,2);
    putImagePosition(box7,205,140,2);
    putImagePosition(box8,275,140,2);
    putImagePosition(box9,205,210,2);
    putImagePosition(box10,350,75,1);
    putImagePosition(box11,280,145,1);
    putImagePosition(box12,210,215,1);
    putImagePosition(box13,140,145,1);
    putImagePosition(box14,70,75,1);
    putImagePosition(box15,140,75,1);
    putImagePosition(box16,280,75,1);
    putImagePosition(box17,210,145,1);
    putImagePosition(box18,210,75,1);

    //cactus structure
    Texture2D *textureSprite = Director::getInstance()->getTextureCache()->addImage("tiles_spritesheet.png");
    auto cactus = Sprite::createWithTexture(textureSprite,Rect(842,720,60,140));
    putImagePosition(cactus,420,105,2);

    //signs structure
    auto sign = getSubImage(288,432);
    auto sign2 = getSubImage(288,432);
    auto sign3 = getSubImage(288,288);
    putImagePosition(sign,100,70,3);
    putImagePosition(sign2,380,70,3);
    putImagePosition(sign3,280,70,3);

    //door structure
    auto doorTop = getSubImage(648,360);
    auto doorMid = getSubImage(648,432);
    putImagePosition(doorTop,205,140,3);
    putImagePosition(doorMid,205,70,3);

    //torch structure
    auto torch = getSubImage(72,144);
    auto torch2 = getSubImage(72,144);
    putImagePosition(torch,135,140,3);
    putImagePosition(torch2,275,140,3);

    //bridge structure
    auto bridge = getSubImage(288,720);
    putImagePosition(bridge,350,190,3);

    //player structure
    auto player = getSubImage(432,360);
    putImagePosition(player,350,212,4);

    //gets the background of the menu
    Texture2D *textureBackGround = Director::getInstance()->getTextureCache()->addImage("bg_desert.png");
    Size sizeTexture = textureBackGround->getContentSize();
    Sprite *spriteBg = Sprite::createWithTexture(textureBackGround,
                                                 Rect(0, 0, visibleSize.width , visibleSize.height));
    //this->addChild(spriteBg, 0);
    spriteBg->setScale(1, 1);
    spriteBg->setPosition(0, 0);
    spriteBg->setAnchorPoint(Vec2(0, 0));
    this->addChild(spriteBg, 0);
    //ParallaxNode* pn = ParallaxNode::create();
    //pn->addChild(spriteBg, 0, Vec2(0.5f,1), Vec2(0,0));

    return true;
}

//##############################################################################
//Stops the game when user click on sign close
//##############################################################################

void
Scenes::
MainMenu::closeMenuCallback(cocos2d::Ref *sender) {
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
MainMenu::playMenuCallback(cocos2d::Ref *sender) {
    
    Entities::Sound::getInstance()->playSound("open_door.mp3");

    Entities::Sound::getInstance()->playBackground("background.mp3");
    
    auto doorClosedTop = getSubImage(648,216);
    auto doorClosedMid = getSubImage(648,288);
    putImagePosition(doorClosedTop,205,140,3);
    putImagePosition(doorClosedMid,205,70,3);
    Director::getInstance()->replaceScene(TransitionFade::create(3.f, Scenes::PlayerTestScene::createScene()));
}

//##############################################################################
//Generate sprite from the sprite sheet
//##############################################################################

Sprite*
Scenes::
MainMenu::getSubImage(int x, int y){

    Texture2D *textureSprite = Director::getInstance()->getTextureCache()->addImage("tiles_spritesheet.png");
    auto sprite = Sprite::createWithTexture(textureSprite,Rect(x,y,K_DEFAULT_SIZE_SPRITE,K_DEFAULT_SIZE_SPRITE));

    return sprite;
}

//##############################################################################
//Set the position of the sprite and index in the scene
//##############################################################################

void
Scenes::
MainMenu::putImagePosition(Sprite *sprite, int x, int y, int pos) {
    sprite->setPosition(Vec2(x,y));
    this->addChild(sprite, pos);
}
