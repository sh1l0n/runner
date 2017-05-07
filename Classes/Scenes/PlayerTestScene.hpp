#pragma once

#include "../Entities/Player.hpp"
#include "../Entities/SpeedMarker.hpp"
#include "../Entities/ScreenKiller.hpp"
#include "../Engine2D/TiledMap/BasicBlock.hpp"
#include "../Engine2D/TiledMap/TiledMapController.h"
#include "../Engine2D/RootEntity.hpp"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SceneController.hpp"

USING_NS_CC;

namespace Scenes {
    
    class PlayerTestScene: public Layer,  public TiledMap::TiledMapControllerListener {
        

        public:
        
            virtual bool init() override;
            static int coins;
        
            void menuCloseCallback(cocos2d::Ref* pSender);
        
            void setListener(SceneControllerListener* listener);
        
            static cocos2d::Scene* createScene(SceneControllerListener* listener);
        
            virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
        
            virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
        
            void removeChunckFromScene(const TiledMap::ChunckIdentifiers id) override;
        
            void addChunckToScene(const TiledMap::ChunckIdentifiers id, TiledMap::Chunck* chunck) override;
        
            void update(float) override;
        
            void retryMenuCallback(cocos2d::Ref* sender);
        
            void gameOver(cocos2d::Ref *sender);
        
            void mainMenu(cocos2d::Ref *sender);
        
            void setAudioButton();
        
            void checkAchievement(const Vec2);
        
            void checkAchievementJump();
        
            CREATE_FUNC(PlayerTestScene);

        private:
        
            SceneControllerListener* _listener;
        
            cocos2d::ui::Button* pauseButton, *audioButton;
        
            bool pause = false, dead = false;
        
            const Size WINDOWS_SIZE_IPHONE = Director::getInstance()->getWinSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();

            float deltaCount;
        
            float stepTime;
        
            float deltaCountForMap;
        
            float puntuacion;
        
            TiledMap::TiledMapController _mapController;
        
            Player *player;
        
            SpeedMarker *speedM;
        
            ScreenKiller *screenK;
        
            RootEntity *box;
        
            Sprite* _sprite;
        
            Label *m_labelPuntuacion, *m_labelPause, *retryLabel, *newGameLabel, *closeLabel, *coinsLabel;
        
            Node *_nodeScroll;
            ParallaxNode *parallax;
            ParallaxNode *parallax2;
        
            Vector<TiledMap::BasicBlock*> boxes;
        
            Node* menu;
        

            Size visibleSize;
        
            int totalJumps = 0, achievementOk = 0;
        
            Color4B blackColor = Color4B(0,0,0,255);
        
            //const float SIZE_BUTTON = 0.1;
            const float SPACE_BUTTON_PADDING = 20;
        
            void createMenuPause();
        
        
    };
}
