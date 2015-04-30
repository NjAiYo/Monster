//
//  Troop.h
//  BGT
//
//  Created by John Running on 15/3/23.
//
//

#ifndef __BGT__Troop__
#define __BGT__Troop__

//有若干的unit组成，
#include "cocos2d.h"
#include "Utils.h"
#include "Unit.h"

class Troop : public cocos2d::Ref
{
    //普通时间模式，troop里的所有怪物都在这个时间点出发
    //完全随机时间模式，troop里的所有怪物都在这个时间段里随机挑一个时间出发
    //线性时间模式，troop里的所有怪物都在这个时间段里线性的出发,每个怪物时间间隔不一定完全一样，有一点点随机偏移

public:
    TroopTimeMode timeMode;
    TroopPositionMode positionMode;
    float beginTime,endTime;
    TroopMonsterMode monsterTypeMode;
    std::vector<Value> typesForRandom;
    
    Troop();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true;};
    
    // implement the "static create()" method manually
    CREATE_FUNC(Troop);
    
    Vector<Unit*> units;
};

#endif /* defined(__BGT__Troop__) */
