//
//  DieState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "DieState.h"
#include "Character.h"
#include <SimpleAudioEngine.h>

void DieState::enter(Character* agent)
{
    //agent->playAnimation(0,"die", true);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "die", false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [] (int trackIndex,int loopCount) {
        //log("attack complete!");
        //agent->move();
    });
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
}

void DieState::execute(Character* agent,float dt)
{
    
}

void DieState::exit(Character* agent)
{
    
}

bool DieState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
