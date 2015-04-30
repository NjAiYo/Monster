//
//  MoveState.cpp
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#include "MoveState.h"
#include "Character.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include "Knife.h"
#include "Utils.h"
#include "BGTWall.h"
#include "AppDelegate.h"

void MoveState::enter(Character* agent)
{
    agent->getSkeletonNode()->setTimeScale(1.0);
    agent->getSkeletonNode()->setToSetupPose();
    agent->getSkeletonNode()->setBonesToSetupPose();
    agent->getSkeletonNode()->setSlotsToSetupPose();
    spTrackEntry* entry = agent->getSkeletonNode()->setAnimation(0, "walk", true);
    agent->getSkeletonNode()->setTrackStartListener(entry, [] (int trackIndex) {
        //log("move start!");
    });

}

void MoveState::execute(Character* agent,float dt)
{
    //检测是否可以攻击门了
    BGTWall *wall = agent->getWorld()->getWall();
    bool canAttack = intersectCircleLine(agent->getPosition(), agent->getAttackRange(), wall->topPosition, wall->bottomPosition);
    
    if (canAttack) {
        agent->attack();
    }else{
        float newX = agent->getPositionX();
        if (agent->getDirection() == CharacterDirectionLeft) {
            newX-=agent->getMoveSpeed()*dt;
        }else{
            newX+=agent->getMoveSpeed()*dt;
        }
        
        agent->setPositionX(newX);
    }
}

void MoveState::exit(Character* agent)
{
    
}

bool MoveState::onMessage(Character* agent, const Telegram& msg)
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