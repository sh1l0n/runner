//
// Created by Pablo Ramon on 6/3/17.
//

#include "Chunck.h"

TiledMap::
Chunck::Chunck() {
    this->_node = Node::create();
    this->_node->retain();
}

TiledMap::
Chunck::~Chunck() {
}
