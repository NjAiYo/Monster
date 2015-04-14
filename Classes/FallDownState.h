//
//  FallDownState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__FallDownState__
#define __BGT__FallDownState__

#include "State.h"
class Character;
struct Telegram;

class FallDownState : public State<Character>
{
private:
    
    
    
    //copy ctor and assignment should be private
    FallDownState(const FallDownState&);
    FallDownState& operator=(const FallDownState&);
    
public:
    explicit FallDownState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__FallDownState__) */
