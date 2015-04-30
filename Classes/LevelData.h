//
//  LevelData.h
//  Monster
//
//  Created by John Running on 15/4/27.
//
//

#ifndef __Monster__LevelData__
#define __Monster__LevelData__

#include "cocos2d.h"
#include "Wave.h"

USING_NS_CC;

class LevelData : public cocos2d::Ref
{
public:
    unsigned int id;
    Vector<Wave*> waves;
    
    LevelData();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true; };
    
    // implement the "static create()" method manually
    CREATE_FUNC(LevelData);
    
    Wave* getWave(int index);
};

#endif /* defined(__Monster__LevelData__) */
