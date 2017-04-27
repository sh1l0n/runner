//
//  SceneController.hpp
//  Runner
//
//  Created by Master Móviles on 26/04/2017.
//
//

#pragma once


namespace Scenes {
    
    enum ESceneType {
        MAIN_MENU = 0x00,
        GAMESCENE = 0x01,
        PAUSE_MENU = 0x02,
        GAMEOVER = 0x03,
        EXIT = 0x04
    };
    
    class SceneControllerListener {

        public:
            virtual void changeScene(ESceneType scene) = 0;
        
            virtual bool getMusic() = 0;
        
            virtual void setMusic(bool music) = 0;
    };
}
