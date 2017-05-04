/*
GameSharing.h

Copyright 2015 Adrian Dawid

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Created by Adrian Dawid on 17.08.14.

*/
#ifndef __GameSharing__
#define __GameSharing__

#include <iostream>
#include "cocos2d.h"
#include <map>
#include <functional>

class GameSharing{
public:

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    static void initGameSharing_iOS(void *initObj);
    /**@brief This function opens the sign in ui, if needed or shows the "Welcome back:..." banner*/
    static bool signInPlayer();
    /**@brief Don't call this function by yourself*/
    static void openGameCenterLeaderboardsUI(int leaderboardID);
    /**@brief Don't call this function by yourself*/
    static void startScoreRequest(int leaderboardID);
    /**@brief Don't call this function by yourself*/
    static void submitScoreToLeaderboard(int score,int leaderboardID);
    /**@brief Don't call this function by yourself*/
    static void unlockAchievement(int achievementID);
    /**@brief Don't call this function by yourself*/
    static void openAchievementUI();
    /**@brief Don't use this variable by yourself*/
    static std::map<int,std::string> iosLeaderboardIds;
    /**@brief Don't use this variable by yourself*/
    static std::map<int,std::string> iosAchievementIds;
    /**@brief Number of Achievements used in this game*/
    static int numberOfAchievements;
    /**@brief Number of Leaderbaords used in this game*/
    static int numberOfLeaderboards;
    
#endif
    
    
};

#endif
