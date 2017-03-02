//
// Created by chancloid on 27/02/2017.
//

#pragma once
#include <vector>
#include "cocos2d.h"
#include "../Structures/StructuresGenerator.hpp"
//#include "Engine2D/Structures/BaseStructure.hpp"
//#include "Engine2D/Structures/MiddlePyramid.hpp"
//#include "../Structures/Pyramid.hpp"
USING_NS_CC;

class MapParser{

public:

    typedef std::vector< std::vector<int> > T_CHUNK;


    static const unsigned char K_WIDTH = 212;
    static const unsigned char K_HEIGHT = 32;
    static const unsigned char K_HEIGHT_FLOOR = 0x02;
    static const unsigned char K_POSITION_X_START = 0x00;
    static const unsigned char K_POSITION_Y_START =0x00+K_HEIGHT_FLOOR;

    static T_CHUNK generateNewChunck() {

        T_CHUNK map;
        map.resize(K_HEIGHT);

        for(unsigned int i=0; i<K_HEIGHT; ++i) {
            map[i].resize(K_WIDTH, false);

        }

        Structures::BaseStructure* bs = Structures::StructuresGenerator::getStructureMatrix();
        std::string chainStructure = "";
        unsigned int i,j;
        for(i=0; i<bs->getHeight(); ++i) {
            for(j=0; j<bs->getWidth(); ++j) {
                chainStructure+=  bs->getDataAt(i, j)?"1 ":"0 ";
            }
            chainStructure +="\n";
        }
        std::cout<<chainStructure;
        std::cout<<"\n\n\n\n";

        //Obtenemos la posición relativa para la estrutura en el mapa
        unsigned int startStructureOnOY = K_HEIGHT- K_POSITION_Y_START;
        unsigned int startStructureOnOX = K_POSITION_X_START;
        //unsigned int i,j;

        /*for(i=startStructureOnOY; i<bs->getHeight(); ++i) {
            for(j=startStructureOnOX; j<bs->getWidth(); ++j) {
                map[i][j] = bs->getDataAt(i, j);
            }
        }*/
        unsigned int posicionChunkX, posicionChunkY;

        for(i=0;i<bs->getHeight();i++){
            for(j=0;j<bs->getWidth();j++){
                posicionChunkX=j+startStructureOnOX;
                posicionChunkY=i+startStructureOnOY -1 -K_HEIGHT_FLOOR;
                map[posicionChunkY][posicionChunkX]=bs->getDataAt(i,j);
            }
        }
        //ponemos el suelo
        int inicioSuelo=K_HEIGHT-1;
        int finSuelo=K_HEIGHT-K_HEIGHT_FLOOR;
        for(i=inicioSuelo;i>=finSuelo;i--){
            for(j=0;j<K_WIDTH;j++){
                map[i][j]=2;
            }
        }


        return map;
    }


    static Node * createMapNode(T_CHUNK map){
        unsigned int i,j;
        //nodo con el chunk
        Node *nodo= Node::create();

        //esto es temporal, después se añadirá una entidad mapa
        Sprite *sprite=NULL;

      /*  sprite=Sprite::create("CloseNormal.png");
        sprite->setPosition(40,40);
        nodo->addChild(sprite);

        sprite=Sprite::create("CloseNormal.png");
        sprite->setPosition(80,80);
        nodo->addChild(sprite);*/


        for(i=0;i<K_HEIGHT-1;i++){
            for(j=0;j<K_WIDTH-1;j++){
                if(map[i][j]==1){
                    //TO DO en lugar de un sprtie añadir un nodo Tile de tipo muro, con sus colisiones
                    sprite=Sprite::create("CloseNormal.png");
                    //esto deberá ser constante por ahora así
                     float ancho=sprite->getContentSize().width;
                     float alto=sprite->getContentSize().height;
                     float posX=j*ancho;
                     float posY=(K_HEIGHT-i)*alto;

                    sprite->setPosition(Vec2(posX,posY));
                    nodo->addChild(sprite);


                }
                if(map[i][j]==2){
                    //TO DO en lugar de un sprtie añadir un nodo Tile de tipo muro, con sus colisiones
                    sprite=Sprite::create("CloseSelected.png");
                    //esto deberá ser constante por ahora así
                    float ancho=sprite->getContentSize().width;
                    float alto=sprite->getContentSize().height;
                    float posX=j*ancho;
                    float posY=(K_HEIGHT-i)*alto;

                    sprite->setPosition(Vec2(posX,posY));
                    nodo->addChild(sprite);

                }

            }
        }


        return nodo;

    }


private:




};


