//
//  FlowState.cpp
//  BGT
//
//  Created by John Running on 15/3/15.
//
//

#include "FlowState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"

void FlowState::enter(Character* agent)
{
    //agent->playAnimation(0,"Injured", false);
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "die", false);
    //agent->getSkeletonNode()->addAnimation(0, "laydown", true);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        //agent->move();
    });
    flowForce = 16;
    ay = flowForce;
    flowForce = 8;
}

void FlowState::execute(Character* agent,float dt)
{
    bool hitFloor = false;
    ay += gravity * dt;
    float newY = ay + agent->getPositionY();
    if (newY <= agent->getFloor()) {
        newY = agent->getFloor();
        hitFloor = true;
    }
    agent->setPositionY(newY);
    if (hitFloor) {
        if (agent->getLife() <= 0) {
            agent->die();
        }else{
            agent->standup();
        }
    }
}

void FlowState::exit(Character* agent)
{
    
}

bool FlowState::onMessage(Character* agent, const Telegram& msg)
{
    switch (msg.msg) {
        case Msg_AttackedByWeapon:{//被玩家的武器攻击到
            log("Character::Msg_AttackedByWeapon");
            Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            agent->takeDamage(weapon->getDamage());

            spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "Injured", false);
            agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
                //agent->getSkeletonNode()->addAnimation(0, "laydown", true);
            });
            switch (weapon->getType()) {
                case WeaponTypeKnife:{
                    Knife *knife = (Knife*)weapon;
                    KnifeAttackDirection direction = *(KnifeAttackDirection*)msg.extraInfo;
                    

                    if (knife->isXuliStateDamage()) {
                        
                        if (direction == KnifeAttackDirectionUp) {
                            //agent->flowup();
                            if (flowForce < 0) {
                                flowForce = 0;
                            }
                            ay += flowForce;
                            flowForce-=2;
                            
                        }else if (direction == KnifeAttackDirectionDown) {
                            //agent->falldown();
                            ay -= 8;
                        }else{
                            //agent->stiff();
                        }
                    }else{
                        ay += 2;
                    }

                }
                    break;
                case WeaponTypePistol:
  
                    break;
                default:
                    break;
            }
        }
            break;
        default:
            break;
    }
    return false;
}
