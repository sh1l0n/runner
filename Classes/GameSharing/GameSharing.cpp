/*
 GameSharing.cpp
 
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



#include "GameSharing.h"

USING_NS_CC;

bool GameSharing::bIsGPGAvailable = true;
bool GameSharing::wasGPGAvailableCalled = false;
std::function<void()> GameSharing::errorHandler;
int GameSharing::localPlayerScore = -1;
bool GameSharing::requestIsBeingProcessed = false;
std::function<void()> GameSharing::requestCallback;

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
std::map<int,std::string> GameSharing::iosLeaderboardIds = std::map<int,std::string>();
std::map<int,std::string> GameSharing::iosAchievementIds = std::map<int,std::string>();
int GameSharing::numberOfAchievements = 0;
int GameSharing::numberOfLeaderboards = 0;

#endif


void GameSharing::initGameSharing(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    //iOS only:
    //Load the data from ios_ids.plist.
    ValueMap ids = FileUtils::getInstance()->getValueMapFromFile("ios_ids.plist");
    //Request the "Achievements" vector from the file.
    ValueVector aIds = ids.at("Achievements").asValueVector();
    //Request the "Leaderboards" vector from the file.
    ValueVector lIds = ids.at("Leaderboards").asValueVector();
    for (int i=0;i<aIds.size();i++) {
        //Copy the achievement IDs for later use.
        iosAchievementIds[i] = aIds.at(i).asString();
        numberOfAchievements=i+1;
    }
    for (int i=0;i<lIds.size();i++) {
        //Copy the leaderboard IDs for later use.
        iosLeaderboardIds[i] = lIds.at(i).asString();
        numberOfLeaderboards=i+1;
    }
    //Show the "Sign In" window.
    signInPlayer();
#endif
    
}

void GameSharing::SubmitScore(int score,int leaderboardID)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    //iOS only:
    //Call the submit Score function (implemented in Objective-C++).
    submitScoreToLeaderboard(score,leaderboardID);
#endif
}

void GameSharing::ShowLeaderboards(int id){

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    //Call the Objective-c++ code.
    openGameCenterLeaderboardsUI(id);
#endif
}

void GameSharing::UnlockAchivement(int ID)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    unlockAchievement(ID);
#endif
}

void GameSharing::ShowAchievementsUI(){

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    openAchievementUI();
#endif
}

bool GameSharing::IsGPGAvailable(){
    bool tmp = false;

    return tmp;
}

void GameSharing::ExitGame(){

    Director::getInstance()->end();
}


void GameSharing::ActivateStdErrorHandler(){

#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    SetErrorHandler([]() -> void{
        MessageBox("A problem with Game Center was encountered.", "Error");
        return;
    });
#endif
}

void GameSharing::RequestCurrentScoreFromLeaderboard(int leaderboardID,std::function<void()> callback)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    GameSharing::startScoreRequest(leaderboardID);
    requestIsBeingProcessed = true;
#endif

    if(callback)
    {
        requestCallback = callback;
    }
}

void GameSharing::SetErrorHandler(std::function<void ()> handler){
    errorHandler = handler;
}
