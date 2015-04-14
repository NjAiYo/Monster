//
//  StandState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__StandState__
#define __BGT__StandState__

#include "State.h"
class Character;
struct Telegram;

class StandState : public State<Character>
{
private:
    
    
    
    //copy ctor and assignment should be private
    StandState(const StandState&);
    StandState& operator=(const StandState&);
    
public:
    explicit StandState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};


#endif /* defined(__BGT__StandState__) */
