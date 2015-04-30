//
//  DieState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__DieState__
#define __BGT__DieState__

#include "State.h"
class Character;
struct Telegram;

class DieState : public State<Character>
{
private:
    
    float deadTime;
    
    //copy ctor and assignment should be private
    DieState(const DieState&);
    DieState& operator=(const DieState&);
    
public:
    explicit DieState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__DieState__) */
