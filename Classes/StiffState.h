//
//  StiffState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__StiffState__
#define __BGT__StiffState__

#include "State.h"
class Character;
struct Telegram;

class StiffState : public State<Character>
{
private:
    bool canMove;
    bool attacked;
    double startTime;
    //copy ctor and assignment should be private
    StiffState(const StiffState&);
    StiffState& operator=(const StiffState&);
    
public:
    explicit StiffState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__StiffState__) */
