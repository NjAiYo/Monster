//
//  DizzyState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__DizzyState__
#define __BGT__DizzyState__

#include "State.h"
class Character;
struct Telegram;

class DizzyState : public State<Character>
{
private:
    
    double startTime;
    
    //copy ctor and assignment should be private
    DizzyState(const DizzyState&);
    DizzyState& operator=(const DizzyState&);
    
public:
    explicit DizzyState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__DizzyState__) */
