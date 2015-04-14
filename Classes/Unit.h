//
//  Unit.h
//  BGT
//
//  Created by John Running on 15/3/23.
//
//

#ifndef __BGT__Unit__
#define __BGT__Unit__


//可以指定兵种，分配出兵时间点
#include "cocos2d.h"
#include "Utils.h"

class Unit : public cocos2d::Ref
{
    CC_SYNTHESIZE(double, _time, Time);//出动时间
    CC_SYNTHESIZE(CharacterType, _type, Type);//类型
    CC_SYNTHESIZE(Vec2, _position, Position);//出动启始位置
    CC_SYNTHESIZE(bool, _randomPosition, RandomPosition);//启始位置是否随机
    CC_SYNTHESIZE(bool, _addRandomTime, AddRandomTime);//出动时间是否加一个随机范围，1-3秒的随机
public:
    Unit();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true;};
    
    // implement the "static create()" method manually
    CREATE_FUNC(Unit);
};

#endif /* defined(__BGT__Unit__) */
