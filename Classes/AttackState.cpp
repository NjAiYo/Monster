//
//  AttackState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "AttackState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"
#include "MessageDispatcher.h"
#include "BGTWall.h"

void AttackState::attack(Character* agent)
{
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "attack", false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        BGTWall *wall = agent->getWorld()->getWall();
        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                          agent->getID(),           //sender ID
                                                          wall->getID(),           //receiver ID
                                                          Msg_WallDamaged,        //msg
                                                          NULL);
    });
}

void AttackState::bigAttack(Character* agent)
{
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "bigattack", false);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        BGTWall *wall = agent->getWorld()->getWall();
        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                                          agent->getID(),           //sender ID
                                                          wall->getID(),           //receiver ID
                                                          Msg_WallDamaged,        //msg
                                                          NULL);
    });
}

void AttackState::enter(Character* agent)
{
    agent->getSkeletonNode()->setTimeScale(1.0);
    agent->getSkeletonNode()->setToSetupPose();
    agent->getSkeletonNode()->setBonesToSetupPose();
    agent->getSkeletonNode()->setSlotsToSetupPose();
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "attack", true);
    agent->getSkeletonNode()->setTrackCompleteListener(entry, [=] (int trackIndex,int loopCount) {
        //log("attack complete!");
        BGTWall *wall = agent->getWorld()->getWall();
        MessageDispatcher::getInstance()->dispatchMessage(0,                  //time delay 1.5
                                    agent->getID(),           //sender ID
                                    wall->getID(),           //receiver ID
                                    Msg_WallDamaged,        //msg
                                    NULL);
    });
}

void AttackState::execute(Character* agent,float dt)
{
    
}

void AttackState::exit(Character* agent)
{
    
}

bool AttackState::onMessage(Character* agent, const Telegram& msg)
{
    switch (msg.msg) {
        case Msg_AttackedByWeapon:{//被玩家的武器攻击到
            log("Character::Msg_AttackedByWeapon");
            Weapon *weapon = (Weapon*)GameEntityManager::getInstance()->getEntityFromID(msg.sender);
            agent->takeDamage(weapon->getDamage());
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
