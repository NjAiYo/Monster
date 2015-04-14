//
//  Character.cpp
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#include "Character.h"
#include "AppDelegate.h"
#include "BGTWall.h"
#include "GameEntityManager.h"
#include "Weapon.h"
#include <SimpleAudioEngine.h>


Character::Character()
:skeletonNode(NULL)
,floor(0)
{

}

Character::~Character()
{
    m_pStateMachine->release();
    standState->release();
    attackState->release();
    fallDownState->release();
    dizzyState->release();
    injureState->release();
    standUpState->release();
    stiffState->release();
    rollBackState->release();
    dieState->release();
    moveState->release();
    lieDownState->release();
    flowState->release();
}

bool Character::initWithWorldAndType(BGTWorld *w,CharacterType t)
{
    if (!GameEntity::initWithWorld(w)) {
        return false;
    }

    dispatcher = MessageDispatcher::getInstance();
    //set up state machine
    m_pStateMachine = new StateMachine<Character>(this);
    
    standState = new StandState();
    attackState = new AttackState();
    fallDownState = new FallDownState();
    dizzyState = new DizzyState();
    injureState = new InjureState();
    standUpState = new StandUpState();
    stiffState = new StiffState();
    rollBackState = new RollBackState();
    dieState = new DieState();
    moveState = new MoveState();
    lieDownState = new LieDownState();
    flowState = new FlowState();
    
    wall = world->getWall();
    setType(t);
    reset();
    return true;
}

float Character::getFloor()
{
    return floor;
}

void Character::setFloor(float f)
{
    floor = f;
}

void Character::falldown()
{
    m_pStateMachine->changeState(fallDownState);
}

void Character::standup()
{
    m_pStateMachine->changeState(standUpState);
}

void Character::move()
{
    m_pStateMachine->changeState(moveState);
}

//for animation
//void Character::playAnimation(int trackIndex, const char* animationName,bool loop)
//{
//    skeletonNode->setToSetupPose();
//    skeletonNode->setBonesToSetupPose();
//    skeletonNode->setSlotsToSetupPose();
//    skeletonNode->setAnimation(trackIndex, animationName, loop);
//}

Rect Character::getRect()
{
    if (m_pStateMachine->isInState(*lieDownState)||m_pStateMachine->isInState(*flowState)||m_pStateMachine->isInState(*injureState)||m_pStateMachine->isInState(*dieState)) {
        return Rect(getPositionX(), getPositionY()-soldierWidth/2, soldierHeight, soldierWidth);
    }else{
        return Rect(getPositionX()-soldierWidth/2, getPositionY(), soldierWidth, soldierHeight);
    }
}

SkeletonAnimation* Character::getSkeletonNode()
{
    return skeletonNode;
}

void Character::reset()
{
    moveSpeed = 40;
    attackSpeed = 1;

    setDirection(CharacterDirectionLeft);
    life = totalLife = 100;
    m_pStateMachine->setCurrentState(standState);
    m_pStateMachine->changeState(standState);
}

bool Character::handleMessage(const Telegram& msg)
{
    return m_pStateMachine->handleMessage(msg);
}

void Character::update(float dt)
{
    m_pStateMachine->update(dt);
}

StateMachine<Character>* Character::getFSM()
{
    return m_pStateMachine;
}

bool Character::isFlowState()
{
    return m_pStateMachine->isInState(*flowState);
}

bool Character::isStandState()
{
    return m_pStateMachine->isInState(*standState);
}

bool Character::isMoveState()
{
    return m_pStateMachine->isInState(*moveState);
}

bool Character::isAttackState()
{
    return m_pStateMachine->isInState(*attackState);
}

bool Character::isFallDownState()
{
    return m_pStateMachine->isInState(*fallDownState);
}

bool Character::isDizzyState()
{
    return m_pStateMachine->isInState(*dizzyState);
}

bool Character::isInjureState()
{
    return m_pStateMachine->isInState(*injureState);
}

bool Character::isStandUpState()
{
    return m_pStateMachine->isInState(*standUpState);
}

bool Character::isStiffState()
{
    return m_pStateMachine->isInState(*stiffState);
}

bool Character::isRollBackState()
{
    return m_pStateMachine->isInState(*rollBackState);
}

bool Character::isLieDownState()
{
    return m_pStateMachine->isInState(*lieDownState);
}

bool Character::isDieState()
{
    return m_pStateMachine->isInState(*dieState);
}

void Character::dizzy()
{
    m_pStateMachine->changeState(dizzyState);
}

void Character::liedown()
{
    m_pStateMachine->changeState(lieDownState);
}

void Character::stiff()
{
    m_pStateMachine->changeState(stiffState);
}

void Character::attack()
{
    m_pStateMachine->changeState(attackState);
}

void Character::flowup()
{
    m_pStateMachine->changeState(flowState);
}

void Character::rollback()
{
    m_pStateMachine->changeState(rollBackState);
}

void Character::takeDamage(float value)
{
    if (life <= 0 || value <= 0) {
        return;
    }
    life -= value;
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
}

void Character::setDirection(CharacterDirection d)
{
    direction = d;
    switch (direction) {
            //        case kUp:
            //            self.rotation = -90;
            //            break;
            //        case kDown:
            //            self.rotation = 90;
            //            break;
        case CharacterDirectionLeft:
            skeletonNode->setScaleX(1);
            break;
        case CharacterDirectionRight:
            skeletonNode->setScaleX(-1);
            break;
        default:
            break;
    }
}

CharacterDirection Character::getDirection()
{
    return direction;
}

void Character::setState(State<Character>* d)
{
    m_pStateMachine->changeState(d);
}

State<Character>* Character::getState()
{
    return m_pStateMachine->currentState();
}

void Character::setType(CharacterType d)
{
    type = d;
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    if(skeletonNode){
        skeletonNode->removeFromParent();
        skeletonNode = NULL;
    }
    switch (type) {
        case CharacterTypeSmallZombie:{
            spAtlas* atlas = spAtlas_createFromFile( "smallzombie.atlas", 0);
            skeletonNode = SkeletonAnimation::createWithFile("smallzombie.json", atlas, 0.45f * scaleFactory);
            attackRange = 250.0f * scaleFactory;
            moveSpeed = 120.0f * scaleFactory;
            soldierWidth = 457.0f * 0.45f * scaleFactory;
            soldierHeight = 748.0f * 0.45f * scaleFactory;
            
//            //所有动画播放一遍，不然会有卡顿现象
//            skeletonNode->setAnimation(0, "Injured", false);
//            skeletonNode->setAnimation(0, "attack", false);
//            skeletonNode->setAnimation(0, "bigattack", false);
//            skeletonNode->setAnimation(0, "die", false);
//            skeletonNode->setAnimation(0, "dizzy", false);
//            skeletonNode->setAnimation(0, "layback", false);
//            skeletonNode->setAnimation(0, "stand", false);
//            skeletonNode->setAnimation(0, "stiff", false);
//            skeletonNode->setAnimation(0, "up", false);
//            skeletonNode->setAnimation(0, "walk", false);
        }
            break;
            
        default:
            break;
    }
    
    //skeletonNode->setAnimation(0, "walk", true);
    //        spine::SkeletonAnimation *skeletonNode = SkeletonAnimation::createWithFile("hero.json", "hero.atlas", 0.6f);
    //        skeletonNode->setAnimation(0, "daiji", true);
    skeletonNode->setPosition(0, 0);
    addChild(skeletonNode);
    //skeletonNode->setAnimation(0, "stand", true);
    
    
//    skeletonNode->setAnimationListener(this, animationStateEvent_selector(Character::animationStateEvent));
    
//    skeletonNode->setStartListener( [this] (int trackIndex) {
//        spTrackEntry* entry = spAnimationState_getCurrent(skeletonNode->getState(), trackIndex);
//        const char* animationName = (entry && entry->animation) ? entry->animation->name : 0;
//        
//        if (m_pStateMachine->isInState(*attackState)) {
//            log("%d start: %s", trackIndex, animationName);
//        }
//    });
//    skeletonNode->setEndListener( [this] (int trackIndex) {
//        if (m_pStateMachine->isInState(*attackState)){
//            log("%d end", trackIndex);
//        }
//    });
//    skeletonNode->setCompleteListener( [this] (int trackIndex, int loopCount) {
////        if (m_pStateMachine->isInState(*attackState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            BGTWall *wall = world->getWall();
////            dispatcher->dispatchMessage(0,                  //time delay 1.5
////                                      getID(),           //sender ID
////                                      wall->getID(),           //receiver ID
////                                      Msg_WallDamaged,        //msg
////                                      NULL);
////        }else if(m_pStateMachine->isInState(*stiffState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            //BGTWall *wall = world->getWall();
////            m_pStateMachine->changeState(moveState);
////        }else if(m_pStateMachine->isInState(*fallDownState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            //BGTWall *wall = world->getWall();
////            m_pStateMachine->changeState(standUpState);
////        }else if(m_pStateMachine->isInState(*standUpState)){
////            log("%d complete: %d", trackIndex, loopCount);
////            //send a delayed message myself so that I know when to take the stew
////            //out of the oven
////            //BGTWall *wall = world->getWall();
////            m_pStateMachine->changeState(moveState);
////        }
//    });
//    skeletonNode->setEventListener( [this] (int trackIndex, spEvent* event) {
//        if (m_pStateMachine->isInState(*attackState)){
//            log("%d event: %s, %d, %f, %s", trackIndex, event->data->name, event->intValue, event->floatValue, event->stringValue);
//        }
//    });
    
    
//    void setTrackStartListener (spTrackEntry* entry, const StartListener& listener);
//    void setTrackEndListener (spTrackEntry* entry, const EndListener& listener);
//    void setTrackCompleteListener (spTrackEntry* entry, const CompleteListener& listener);
//    void setTrackEventListener (spTrackEntry* entry, const EventListener& listener);
    
//    virtual void onAnimationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);
//    virtual void onTrackEntryEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);
    
    setDirection(direction);
}

void Character::animationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount)
{
    
}

CharacterType Character::getType()
{
    return type;
}

void Character::setTotalLife(float d)
{
    totalLife = d;
}

float Character::getTotalLife()
{
    return totalLife;
}

void Character::setLife(float d)
{
    life = d;
}

float Character::getLife()
{
    return life;
}

void Character::setSoldierWidth(float d)
{
    soldierWidth = d;
}

float Character::getSoldierWidth()
{
    return soldierWidth;
}

void Character::setSoldierHeight(float d)
{
    soldierHeight = d;
}

float Character::getSoldierHeight()
{
    return soldierHeight;
}

void Character::setHeightFromFloor(float d)
{
    heightFromFloor = d;
}

float Character::getHeightFromFloor()
{
    return heightFromFloor;
}

void Character::setMoveSpeed(float d)
{
    moveSpeed = d;
}

float Character::getMoveSpeed()
{
    return moveSpeed;
}

void Character::setAttackSpeed(float d)
{
    attackSpeed = d;
}

float Character::getAttackSpeed()
{
    return attackSpeed;
}

void Character::setDamage(float d)
{
    damage = d;
}

float Character::getDamage()
{
    return damage;
}

void Character::setIsRemoteSoldier(bool d)
{
    isRemoteSoldier = d;
}

bool Character::getIsRemoteSoldier()
{
    return isRemoteSoldier;
}

void Character::setAttackRange(float d)
{
    attackRange = d;
}

float Character::getAttackRange()
{
    return attackRange;
}

