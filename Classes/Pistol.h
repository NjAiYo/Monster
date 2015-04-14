//
//  Pistol.h
//  BGT
//
//  Created by John Running on 15/3/14.
//
//

#ifndef __BGT__Pistol__
#define __BGT__Pistol__

#include "cocos2d.h"
#include "Weapon.h"


USING_NS_CC;

class Pistol : public Weapon
{
private:
    double shotInteval;
    bool canShot;
    double lastShotTime;
public:
    
    bool initWithWorld(BGTWorld *w);
    
    //all subclasses can communicate using messages.
    bool  handleMessage(const Telegram& msg);
    //all entities must implement an update function
    void update(float dt);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
};


#endif /* defined(__BGT__Pistol__) */
