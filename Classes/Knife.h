//
//  Knife.h
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#ifndef __BGT__Knife__
#define __BGT__Knife__

#include "cocos2d.h"
#include "Weapon.h"


USING_NS_CC;

class Knife : public Weapon
{
private:
    //Sprite* star;
    MotionStreak* streak;
    Vec2 startTouchPosition;
    bool touchedForXuLi;
    double currentTouchTime;
    Layer *xuliLayer;

    ProgressTimer *xuliBar;

public:
    bool initWithWorld(BGTWorld *w);
    
    bool isXuliStateDamage();
    
    //all subclasses can communicate using messages.
    bool  handleMessage(const Telegram& msg);
    //all entities must implement an update function
    void update(float dt);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif /* defined(__BGT__Knife__) */
