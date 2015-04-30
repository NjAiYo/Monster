//
//  RollBackState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "RollBackState.h"
#include "Character.h"

void RollBackState::enter(Character* agent)
{
    log("RollBackState::enter");
    backforce = 600;
    friction = 0.92;
    //agent->playAnimation(0,"rollback", true);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "stiff", false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        
        if (agent->isRollBackState()) {
            //播放后仰的动画
            //agent->getSkeletonNode()->setAnimation(0, "layback", true);
        }
    });
}

void RollBackState::execute(Character* agent,float dt)
{
    backforce *= friction;
    float delta = backforce*dt;
    float newX = agent->getPositionX();
    newX+=delta;
    
    agent->setPositionX(newX);
    if (delta <= 1) {
        agent->dizzy();
    }
}

void RollBackState::exit(Character* agent)
{
    
}

bool RollBackState::onMessage(Character* agent, const Telegram& msg)
{
    return false;
}
