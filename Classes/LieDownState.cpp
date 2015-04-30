//
//  LieDownState.cpp
//  BGT
//
//  Created by John Running on 15/3/13.
//
//

#include "LieDownState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"

void LieDownState::enter(Character* agent)
{
    //agent->playAnimation(0,"die", true);
    //spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "laydown", true);
//    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
//
//    });
    startTime = millisecondNow();
}

void LieDownState::execute(Character* agent,float dt)
{
    if (millisecondNow() - startTime >= 1000) {
        agent->standup();
    }
}

void LieDownState::exit(Character* agent)
{
    
}

bool LieDownState::onMessage(Character* agent, const Telegram& msg)
{
    switch (msg.msg) {
        case Msg_AttackedByWeapon:{//被玩家的武器攻击到
            log("Character::Msg_AttackedByWeapon");
            Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            agent->takeDamage(weapon->getDamage());
            if (agent->getLife() <= 0) {
                agent->die();
                return false;
            }
            spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "Injured", false);
            agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
                //agent->getSkeletonNode()->setAnimation(0, "laydown", true);
            });
            switch (weapon->getType()) {
                case WeaponTypeKnife:{
                    Knife *knife = (Knife*)weapon;
                    
                    

                    if (knife->isXuliStateDamage()) {
                        KnifeAttackDirection direction = *(KnifeAttackDirection*)msg.extraInfo;
                        if (direction == KnifeAttackDirectionUp) {
                            agent->flowup();
                        }else if (direction == KnifeAttackDirectionDown) {
                            //agent->falldown();
                        }else{
                            //agent->stiff();
                        }
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