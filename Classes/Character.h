//
//  Character.h
//  BGT
//
//  Created by John Running on 15/3/4.
//
//

#ifndef __BGT__Character__
#define __BGT__Character__

#include "cocos2d.h"
#include "Utils.h"
#include "BGTWorld.h"
#include "GameEntity.h"
#include "StateMachine.h"
#include "StandState.h"
#include "AttackState.h"
#include "FallDownState.h"
#include "DizzyState.h"
#include "InjureState.h"
#include "StandUpState.h"
#include "StiffState.h"
#include "RollBackState.h"
#include "DieState.h"
#include "MoveState.h"
#include "MessageDispatcher.h"
#include "LieDownState.h"
#include "FlowState.h"
#include "MonsterData.h"

class BGTWall;

template <class entity_type> class State; //pre-fixed with "template <class entity_type> " for vs8 compatibility

struct Telegram;

USING_NS_CC;

class Character : public GameEntity
{
protected:
    //for debug
//    DrawNode *hitRectNode;
    Sprite *lifeBar;
    ProgressTimer *progressBar;
    //states
    StandState *standState;
    AttackState *attackState;
    FallDownState *fallDownState;
    DizzyState *dizzyState;
    InjureState *injureState;
    StandUpState *standUpState;
    StiffState *stiffState;
    RollBackState *rollBackState;
    DieState *dieState;
    MoveState *moveState;
    LieDownState *lieDownState;
    FlowState *flowState;
    
    MessageDispatcher *dispatcher;
    
    CharacterDirection direction;
    //CharacterState state;
    spine::SkeletonAnimation *skeletonNode;
    MonsterData *monsterData;
//    CharacterType type;
    float life;
//    //用于碰撞检测
//    float soldierWidth;
//    float soldierHeight;
    
    //离地面的高度，普通的士兵是0，也就是站在地上，飞行的兵和被打飞起来的兵大于0
    float heightFromFloor;
//    
//    
//    float moveSpeed;
//    //两次攻击之间间隔
//    float attackSpeed;
//    //伤害
//    float damage;
//    //攻击范围，远程兵就是射程
//    float attackRange;
    
    bool  isRemoteSoldier;

    
    BGTWall *wall;
    
    //an instance of the state machine class
    StateMachine<Character>*  m_pStateMachine;
    
    float floor;
    float currentTimeScale;
    
    void animationStateEvent (int trackIndex, spEventType type, spEvent* event, int loopCount);
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithWorldAndType(BGTWorld *world,CharacterType t);
    Character();
    virtual ~Character();
    bool  handleMessage(const Telegram& msg);
    void update(float dt);
    
    Rect getRect();
    
    StateMachine<Character>* getFSM();
    
    SkeletonAnimation* getSkeletonNode();
    
    void pauseAnimation();
    void resumeAnimation();
    
    float getFloor();
    void setFloor(float f);
    
//    void playAnimation(int trackIndex, const char* animationName,bool loop);
    
    bool isStandState();
    bool isMoveState();
    bool isAttackState();
    bool isFallDownState();
    bool isDizzyState();
    bool isInjureState();
    bool isStandUpState();
    bool isStiffState();
    bool isRollBackState();
    bool isDieState();
    bool isLieDownState();
    bool isFlowState();
    
    virtual void reset();
    
    virtual void move();
    virtual void attack();
    virtual void falldown();
    virtual void standup();
    virtual void dizzy();
    virtual void stiff();
    virtual void flowup();
    virtual void rollback();
    virtual void liedown();
    virtual void die();
    
    virtual void takeDamage(float damage);
    
    virtual void setDirection(CharacterDirection d);
    CharacterDirection getDirection();
    
    virtual void setState(State<Character>* d);
    State<Character>* getState();
    
    virtual void setType(CharacterType d);
    CharacterType getType();
    
//    virtual void setTotalLife(float d);
    float getTotalLife();
    
    virtual void setLife(float d);
    float getLife();
    
//    virtual void setSoldierWidth(float d);
    float getSoldierWidth();
//
//    virtual void setSoldierHeight(float d);
    float getSoldierHeight();
    
    virtual void setHeightFromFloor(float d);
    float getHeightFromFloor();
    
//    virtual void setMoveSpeed(float d);
    float getMoveSpeed();
//
//    virtual void setAttackSpeed(float d);
    float getAttackSpeed();
    
//    virtual void setDamage(float d);
    float getDamage();
    
    virtual void setIsRemoteSoldier(bool d);
    bool getIsRemoteSoldier();
    
//    virtual void setAttackRange(float d);
    float getAttackRange();
    
    MonsterData* getMonsterData();
};

#endif /* defined(__BGT__Character__) */
