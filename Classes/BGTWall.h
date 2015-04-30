//
//  BGTWall.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__BGTWall__
#define __BGT__BGTWall__

#include "cocos2d.h"
#include "GameEntity.h"
#include "Telegram.h"
class BGTWorld;

USING_NS_CC;

class BGTWall : public GameEntity
{
private:
    float totalLife;
    float life;
    //门的宽度
    float width;
    
    ProgressTimer *lifeBar;
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithWorld(BGTWorld *world);
    BGTWall();

    bool handleMessage(const Telegram& msg);
    void update(float dt);
    void takeDamage(float value);
    
    float getLife();
    float getTotalLife();
    
    float getWidth();
    
    void reset();
    
    Vec2 topPosition;
    Vec2 bottomPosition;
};

#endif /* defined(__BGT__BGTWall__) */
