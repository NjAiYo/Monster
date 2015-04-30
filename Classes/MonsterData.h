//
//  MonsterData.h
//  Monster
//
//  Created by John Running on 15/4/27.
//
//

#ifndef __Monster__MonsterData__
#define __Monster__MonsterData__

#include "cocos2d.h"
USING_NS_CC;

class MonsterData : public cocos2d::Ref
{

public:
    unsigned int level,life,moveSpeed,exp,damage,defense,type,attackRange;
    std::string name;
    float attackSpeed,baoji,shanbi;
    Rect hitRect;
    Point anchorPoint;
    
    MonsterData();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true; };
    
    // implement the "static create()" method manually
    CREATE_FUNC(MonsterData);
};

#endif /* defined(__Monster__MonsterData__) */
