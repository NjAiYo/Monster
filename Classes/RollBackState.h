//
//  RollBackState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__RollBackState__
#define __BGT__RollBackState__

#include "State.h"
class Character;
struct Telegram;

class RollBackState : public State<Character>
{
private:
    float backforce;
    float friction;
    
    //copy ctor and assignment should be private
    RollBackState(const RollBackState&);
    RollBackState& operator=(const RollBackState&);
    
public:
    explicit RollBackState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__RollBackState__) */
