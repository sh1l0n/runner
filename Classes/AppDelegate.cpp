
#include "Scenes/MainMenuPhone.hpp"
#include "AppDelegate.h"
#include <stdlib.h>
#include <thread>
#include <time.h>


USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480,320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
    srand(time(NULL));
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Runner", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Runner");
        
        
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::EXACT_FIT);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
    //pab
    /*std::cout<<"Content scale"<<MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width)<<"\n";
     director->setContentScaleFactor(3);*/
    //pab

    register_all_packages();
    
    
    this->changeScene(Scenes::ESceneType::MAIN_MENU);

    // create a scene. it's an autorelease object
    //auto scene = PlayerTestScene::createScene();
    //log("hola %d: caracola: %d comadrona: %d",CC_TARGET_PLATFORM,CC_PLATFORM_IOS,CC_PLATFORM_MAC);
   // scene = Scenes::MainMenuPhone::createScene();

    // run
    //director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void
AppDelegate::changeScene(Scenes::ESceneType scene) {
    
    cocos2d::Scene* sceneToLoad;
    
    switch (scene) {
        case Scenes::MAIN_MENU:
            sceneToLoad = Scenes::MainMenuPhone::createScene(this);
            mainMenu = false;
            break;
        case Scenes::GAMESCENE:
            sceneToLoad = Scenes::PlayerTestScene::createScene(this);
            mainMenu = true;
            break;
        case Scenes::GAMEOVER:
            sceneToLoad = Scenes::PlayerTestScene::createScene(this);
            mainMenu = false;
            break;
        case Scenes::EXIT:
            Director::getInstance()->end();
            exit(0);
            break;
        default:
            break;
    }
    log("Music: %d",music);
    
    if(Director::getInstance()->getRunningScene()==NULL) {
        Director::getInstance()->runWithScene(sceneToLoad);
        mainMenu= true;
    }else if(mainMenu){
        Director::getInstance()->pushScene(TransitionFade::create(3.f,sceneToLoad));
        Director::getInstance()->resume();
    }
    else{
        Director::getInstance()->pushScene(sceneToLoad);
    }
}

bool
AppDelegate::getMusic(){
    return this->music;
}

void
AppDelegate::setMusic(bool music){
    this->music = music;
}



