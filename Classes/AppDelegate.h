#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "Scenes/SceneController.hpp"

/**
@brief    The cocos2d Application.

Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private cocos2d::Application, public Scenes::SceneControllerListener
{
private:
    bool mainMenu=false,exitMainMenu = false;
    bool music=true;
    //cocos2d::Scene* scene;
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs() override;

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching() override;

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground() override;

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground() override;
    
    void changeScene(Scenes::ESceneType scene) override;
    
    bool getMusic() override;
    
    void setMusic(bool music) override;
};

#endif // _APP_DELEGATE_H_

