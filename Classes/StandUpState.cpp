//
//  StandUpState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "StandUpState.h"
#include "Character.h"

void StandUpState::enter(Character* agent)
{
    //agent->playAnimation(0,"standup", false);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "up", false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        agent->move();
    });
}

void StandUpState::execute(Character* agent,float dt)
{
    
}

void StandUpState::exit(Character* agent)
{
    
}

bool StandUpState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
