//
//  StandUpState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__StandUpState__
#define __BGT__StandUpState__

#include "State.h"
class Character;
struct Telegram;

class StandUpState : public State<Character>
{
private:
    
    
    
    //copy ctor and assignment should be private
    StandUpState(const StandUpState&);
    StandUpState& operator=(const StandUpState&);
    
public:
    explicit StandUpState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__StandUpState__) */
