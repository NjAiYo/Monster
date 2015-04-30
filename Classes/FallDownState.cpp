//
//  FallDownState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "FallDownState.h"
#include "Character.h"

void FallDownState::enter(Character* agent)
{
    //agent->playAnimation(0,"die", false);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "falldown", false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        agent->liedown();
    });
    
}

void FallDownState::execute(Character* agent,float dt)
{
    
}

void FallDownState::exit(Character* agent)
{
    
}

bool FallDownState::onMessage(Character* agent, const Telegram& msg)
{

    return false;
}
