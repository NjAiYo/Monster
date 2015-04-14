//
//  WeaponState.h
//  BGT
//
//  Created by John Running on 15/3/13.
//
//

#ifndef BGT_WeaponState_h
#define BGT_WeaponState_h
#include "cocos2d.h"
#include "State.h"

USING_NS_CC;

struct Telegram;

template <typename entity_type>
class WeaponState  : public State
{
public:
    virtual bool onTouchBegan(Touch* touch, Event* event)=0;
    virtual void onTouchMoved(Touch* touch, Event* event)=0;
    virtual void onTouchEnded(Touch* touch, Event* event)=0;
    virtual void onTouchCancelled(Touch *touch, Event *unused_event)=0;
    
    virtual ~WeaponState(){}
    
    
};

#endif
