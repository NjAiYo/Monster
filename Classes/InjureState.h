//
//  InjureState.h
//  BGT
//
//  Created by John Running on 15/3/7.
//
//

#ifndef __BGT__InjureState__
#define __BGT__InjureState__

#include "State.h"
class Character;
struct Telegram;

class InjureState : public State<Character>
{
private:
    
    
    
    //copy ctor and assignment should be private
    InjureState(const InjureState&);
    InjureState& operator=(const InjureState&);
    
public:
    explicit InjureState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__InjureState__) */
