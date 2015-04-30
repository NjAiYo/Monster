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
,currentTimeScale(1)
,monsterData(NULL)
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
    if (monsterData) {
        monsterData->release();
    }
}

bool Character::initWithWorldAndType(BGTWorld *w,CharacterType t)
{
    if (!GameEntity::initWithWorld(w)) {
        return false;
    }
    
    lifeBar = Sprite::createWithSpriteFrameName("lifeBarFrame.png");
    lifeBar->setPosition(0,0);
    addChild(lifeBar);
    lifeBar->setVisible(false);
    
    progressBar = ProgressTimer::create(Sprite::createWithSpriteFrameName("lifeBar.png"));
    
    progressBar->setType(ProgressTimer::Type::BAR);
    progressBar->setMidpoint(Vec2(0,1));
    progressBar->setBarChangeRate(Vec2(1, 0));
    progressBar->setPercentage(100);
    progressBar->setPosition(lifeBar->getContentSize().width/2,lifeBar->getContentSize().height/2);
    lifeBar->addChild(progressBar);
    

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
    
//    hitRectNode = DrawNode::create();
//    addChild(hitRectNode,100000);
    
    

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
    //spAttachment *boundingBox = skeletonNode->getAttachment("bodyBound", "bodyBound");
    Rect rect = skeletonNode->getBoundingBox();
    return Rect(getPositionX()+rect.origin.x, getPositionY()+rect.origin.y, rect.size.width, rect.size.height);
//    //hitRectNode->drawRect(rect.origin, Vec2(rect.origin.x+rect.size.width,rect.origin.y+rect.size.height), Color4F(0, 1, 0, 1));
//    //log("getRect");
//    if (m_pStateMachine->isInState(*lieDownState)||m_pStateMachine->isInState(*flowState)||m_pStateMachine->isInState(*injureState)||m_pStateMachine->isInState(*dieState)) {
//        float soldierWidth = monsterData->hitRect.size.width;
//        float soldierHeight = monsterData->hitRect.size.height;
//        return Rect(getPositionX(), getPositionY()-soldierWidth/2, soldierHeight, soldierWidth);
////        Rect rect = Rect(getPositionX()+monsterData->hitRect.origin.x, getPositionY()+monsterData->hitRect.origin.y, getPositionY()+monsterData->hitRect.size.width, getPositionY()+monsterData->hitRect.size.height);
//
////        hitRectNode->drawRect(monsterData->hitRect.origin, Vec2(monsterData->hitRect.origin.x+monsterData->hitRect.size.width,monsterData->hitRect.origin.y+monsterData->hitRect.size.height), Color4F(0, 1, 0, 1));
////
////        return rect;
//    }else{
//        //return Rect(getPositionX()-soldierWidth/2, getPositionY(), soldierWidth, soldierHeight);
//        Rect rect = Rect(getPositionX()+monsterData->hitRect.origin.x, getPositionY()+monsterData->hitRect.origin.y, getPositionY()+monsterData->hitRect.size.width, getPositionY()+monsterData->hitRect.size.height);
//
//        //hitRectNode->drawRect(monsterData->hitRect.origin, Vec2(monsterData->hitRect.origin.x+monsterData->hitRect.size.width,monsterData->hitRect.origin.y+monsterData->hitRect.size.height), Color4F(0, 1, 0, 1));
//
//        return rect;
//    }
}

SkeletonAnimation* Character::getSkeletonNode()
{
    return skeletonNode;
}

void Character::reset()
{
    setDirection(CharacterDirectionLeft);
    life = monsterData->life;
    progressBar->setPercentage(100 *(life/(float)monsterData->life));
    lifeBar->setVisible(false);
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

void Character::die(){
    world->monsterDied(this);
    m_pStateMachine->changeState(dieState);
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
    if (life <= 0) {
        life = 0;
        lifeBar->setVisible(false);
    }else{
        lifeBar->setVisible(true);
    }
    progressBar->setPercentage(100 *(life/(float)monsterData->life));
//    if(life <= 0){
//        m_pStateMachine->changeState(dieState);
//    }
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("dao_1.mp3");
}

void Character::pauseAnimation()
{
    currentTimeScale = skeletonNode->getTimeScale();
    skeletonNode->setTimeScale(0);
}

void Character::resumeAnimation()
{
    skeletonNode->setTimeScale(currentTimeScale);
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
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    if(skeletonNode){
        skeletonNode->removeFromParent();
        skeletonNode = NULL;
    }
    if (monsterData) {
        monsterData->release();
    }
    monsterData = WaveManager::getInstance()->getMonsterDataByType(d);
//#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid monster type: %d", d);
    CCASSERT(monsterData != NULL, msg);
//#endif
    char name[256] = {0};
    sprintf(name, "monster%d.atlas", d);
    spAtlas* atlas = spAtlas_createFromFile(name, 0);
    char name1[256] = {0};
    sprintf(name1, "monster%d.json", d);
    skeletonNode = SkeletonAnimation::createWithFile("skeleton.json", atlas, 0.45f * scaleFactory);
    skeletonNode->setPosition(0, 0);
    addChild(skeletonNode);

    Rect rect = skeletonNode->getBoundingBox();
    lifeBar->setPositionY(monsterData->hitRect.size.height+70);
    
    
    //skeletonNode->setDebugBonesEnabled(true);
//    switch (d) {
//        case CharacterTypeSmallZombie:{
//
////            attackRange = 250.0f * scaleFactory;
////            moveSpeed = 120.0f * scaleFactory;
////            soldierWidth = 457.0f * 0.45f * scaleFactory;
////            soldierHeight = 748.0f * 0.45f * scaleFactory;
//        }
//            break;
//            
//        default:
//            break;
//    }
    
    //skeletonNode->setAnimation(0, "walk", true);
    //        spine::SkeletonAnimation *skeletonNode = SkeletonAnimation::createWithFile("hero.json", "hero.atlas", 0.6f);
    //        skeletonNode->setAnimation(0, "daiji", true);

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
    return (CharacterType)monsterData->type;
}

void Character::setLife(float d)
{
    life = d;
}

float Character::getLife()
{
    return life;
}

//void Character::setTotalLife(float d)
//{
//    totalLife = d;
//}

float Character::getTotalLife()
{
    return monsterData->life;
}

//void Character::setSoldierWidth(float d)
//{
//    soldierWidth = d;
//}

float Character::getSoldierWidth()
{
    return monsterData->hitRect.size.width;
}

//void Character::setSoldierHeight(float d)
//{
//    soldierHeight = d;
//}

float Character::getSoldierHeight()
{
    return monsterData->hitRect.size.height;;
}

void Character::setHeightFromFloor(float d)
{
    heightFromFloor = d;
}

float Character::getHeightFromFloor()
{
    return heightFromFloor;
}

//void Character::setMoveSpeed(float d)
//{
//    moveSpeed = d;
//}

float Character::getMoveSpeed()
{
    return monsterData->moveSpeed;
}

//void Character::setAttackSpeed(float d)
//{
//    attackSpeed = d;
//}

float Character::getAttackSpeed()
{
    return monsterData->attackSpeed;
}

//void Character::setDamage(float d)
//{
//    damage = d;
//}

float Character::getDamage()
{
    return (float)monsterData->damage;
}

void Character::setIsRemoteSoldier(bool d)
{
    isRemoteSoldier = d;
}

bool Character::getIsRemoteSoldier()
{
    return isRemoteSoldier;
}

//void Character::setAttackRange(float d)
//{
//    attackRange = d;
//}

float Character::getAttackRange()
{
    return monsterData->attackRange;
}

MonsterData* Character::getMonsterData()
{
    return monsterData;
}
