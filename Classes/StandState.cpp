//
//  StandState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "StandState.h"
#include "Character.h"

void StandState::enter(Character* agent)
{
    log("StandState::enter");
    //agent->playAnimation(0,"stand", true);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "stand", true);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [] (int trackIndex,int loopCount) {
        //log("attack complete!");

    });
}

void StandState::execute(Character* agent,float dt)
{
    
}

void StandState::exit(Character* agent)
{
    
}

bool StandState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
