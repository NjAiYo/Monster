//
//  FlowState.h
//  BGT
//
//  Created by John Running on 15/3/15.
//
//

#ifndef __BGT__FlowState__
#define __BGT__FlowState__

//腾空
#include "State.h"
class Character;
struct Telegram;

class FlowState : public State<Character>
{
private:
    //copy ctor and assignment should be private
    FlowState(const FlowState&);
    FlowState& operator=(const FlowState&);
    
    float flowForce;
    float ay;
public:
    explicit FlowState(){}
    virtual void enter(Character* agent);
    
    virtual void execute(Character* agent,float dt);
    
    virtual void exit(Character* agent);
    
    virtual bool onMessage(Character* agent, const Telegram& msg);
};

#endif /* defined(__BGT__FlowState__) */
