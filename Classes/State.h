//
//  State.h
//  BGT
//
//  Created by John Running on 15/3/5.
//
//

#ifndef __BGT__State__
#define __BGT__State__
#include "cocos2d.h"

USING_NS_CC;

struct Telegram;

template <typename entity_type>
class State  : public Ref
{
public:
    
    //this executes if the agent receives a message from the
    //message dispatcher
    virtual bool onMessage(entity_type*, const Telegram&)=0;
    virtual void enter(entity_type*)=0;
    
    virtual void execute(entity_type*,float dt)=0;
    
    virtual void exit(entity_type*)=0;
    
    virtual ~State(){}
};

#endif /* defined(__BGT__State__) */
