//
//  AttackState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__AttackState__
#define __BGT__AttackState__

#include "State.h"
class Character;
struct Telegram;

class AttackState : public State<Character>
{
private:
    //copy ctor and assignment should be private
    AttackState(const AttackState&);
    AttackState& operator=(const AttackState&);
    int attackNum;
    bool attacking;
public:
    explicit AttackState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
    
    void attack(Character* agent);
    void bigAttack(Character* agent);
    
};

#endif /* defined(__BGT__AttackState__) */
