//
// Created by Pablo Ramon on 6/3/17.
//

#pragma  once

#include "cocos2d.h"
#include "Engine2D/RootEntity.hpp"
#include "BasicBlock.hpp"

USING_NS_CC;

namespace TiledMap {
    class Chunck {

    public:
        Node *_node;
        Vector<BasicBlock*> _collisionables;
        Chunck();
        ~Chunck();
    };
}

