//
//  DizzyState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "DizzyState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"

void DizzyState::enter(Character* agent)
{
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "dizzy", true);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [] (int trackIndex,int loopCount) {
        //log("attack complete!");

    });
    startTime = millisecondNow();
}

void DizzyState::execute(Character* agent,float dt)
{
    if (millisecondNow() - startTime >= 2000) {
        agent->move();
    }
}

void DizzyState::exit(Character* agent)
{
    
}

bool DizzyState::onMessage(Character* agent, const Telegram& msg)
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
            switch (weapon->getType()) {
                case WeaponTypeKnife:{
                    Knife *knife = (Knife*)weapon;
                    
                    
                    KnifeAttackDirection direction = *(KnifeAttackDirection*)msg.extraInfo;
                    if (knife->isXuliStateDamage()) {
                        if (direction == KnifeAttackDirectionUp) {
                            agent->flowup();
                        }else if (direction == KnifeAttackDirectionDown) {
                            agent->falldown();
                        }else if (direction == KnifeAttackDirectionRight) {
                            agent->rollback();
                        }else{
                            agent->stiff();
                        }
                    }else{
                        agent->stiff();
                    }
                    
                }
                    break;
                case WeaponTypePistol:
                    agent->stiff();
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
