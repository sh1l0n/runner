#pragma once

#include "../Entities/Player.hpp"
#include "../Entities/SpeedMarker.hpp"
#include "../Engine2D/TiledMap/BasicBlock.hpp"
#include "../Engine2D/TiledMap/TiledMapController.h"
#include "../Engine2D/RootEntity.hpp"
#include "cocos2d.h"

USING_NS_CC;

namespace Scenes {
    
    class PlayerTestScene: public Layer,  public TiledMap::TiledMapControllerListener {

        public:
        
            virtual bool init() override;
        
            void menuCloseCallback(cocos2d::Ref* pSender);
        
            static cocos2d::Scene* createScene();
        
            virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
        
            virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
        
            virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
            virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event) override;
        
            void removeChunckFromScene(const TiledMap::ChunckIdentifiers id) override;
        
            void addChunckToScene(const TiledMap::ChunckIdentifiers id, TiledMap::Chunck* chunck) override;
        
            void update(float) override;
        
            CREATE_FUNC(PlayerTestScene);

        private:

            float deltaCount;
        
            float stepTime;
        
            float deltaCountForMap;
        
            float puntuacion;
        
            TiledMap::TiledMapController _mapController;
        
            Player *player;
        
            SpeedMarker *speedM;
        
            RootEntity *box;
        
            Sprite* _sprite;
        
            Label *m_labelPuntuacion;
        
            Node *_nodeScroll;
        
            Vector<TiledMap::BasicBlock*> boxes;
    };
}
