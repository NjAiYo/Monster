//
//  MoveState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__MoveState__
#define __BGT__MoveState__

#include "State.h"
class Character;
struct Telegram;

class MoveState : public State<Character>
{
private:
    //copy ctor and assignment should be private
    MoveState(const MoveState&);
    MoveState& operator=(const MoveState&);

public:
    explicit MoveState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__MoveState__) */
