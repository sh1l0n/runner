//
// Created by juancarlos on 26/02/17.
//
#pragma once


#include <Entities/Player.hpp>

#include <Entities/SpeedMarker.hpp>
#include <Engine2D/TiledMap/BasicBlock.hpp>
#include "../../Engine2D/RootEntity.hpp"


#include "cocos2d.h"

USING_NS_CC;

class PlayerTestScene: public Layer {

    public:
    virtual bool init();
    void menuCloseCallback(cocos2d::Ref* pSender);
    static cocos2d::Scene* createScene();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void update(float) override;
    CREATE_FUNC(PlayerTestScene);

    private:

        float deltaCount, stepTime,deltaCountForMap;

        int numWorld;
        int worldSizePx;
        Player *e;
        SpeedMarker *speedM;
        RootEntity *box;
        //GUI *gui;
        Label *m_labelPuntuacion;
        float puntuacion;
        Node *m_scroll;
        Node *world1;
        Node *world2;
        TiledMap::Chunck chunk1;
        TiledMap::Chunck chunk2;
        Vector<TiledMap::BasicBlock*> boxes;
};

