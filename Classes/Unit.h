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
public:
    int type;//出动时间//-1表示随机
    int x,y;//
    bool isRandomPosition;//是否是随机位置,isRandomPosition为true   不使用x，y的属性
    
    //出发时间，在wave生成的unit中使用
    float outTime;
    Vec2 outPosition;
    int outType;
    bool  outed;//是否已经发出
    Unit();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true;};
    
    // implement the "static create()" method manually
    CREATE_FUNC(Unit);
};

#endif /* defined(__BGT__Unit__) */
