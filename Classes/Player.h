//
//  Player.h
//  Monster
//
//  Created by John Running on 15/4/29.
//
//

#ifndef __Monster__Player__
#define __Monster__Player__

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Ref
{
public:
    unsigned int id,level,score,money;
    std::string name;
    float exp,enegy;
    
    ~Player();
    Player();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(Player);
};

#endif /* defined(__Monster__Player__) */
