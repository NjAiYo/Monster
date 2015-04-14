//
//  InjureState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "InjureState.h"
#include "Character.h"

void InjureState::enter(Character* agent)
{
    //agent->playAnimation(0,"injure", true);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "injure", true);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [] (int trackIndex,int loopCount) {
        //log("attack complete!");
        
    });
}

void InjureState::execute(Character* agent,float dt)
{
    
}

void InjureState::exit(Character* agent)
{
    
}

bool InjureState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
