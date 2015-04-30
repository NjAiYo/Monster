//
//  Wave.h
//  Monster
//
//  Created by John Running on 15/4/27.
//
//

#ifndef __Monster__Wave__
#define __Monster__Wave__

#include "cocos2d.h"
#include "Troop.h"

USING_NS_CC;

class Wave : public cocos2d::Ref
{
    Vector<Unit*> allUnits;
public:
    unsigned int id;
    Vector<Troop*> troops;
    Wave();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true; };
    
    // implement the "static create()" method manually
    CREATE_FUNC(Wave);
    
    void generateUnitsDataForBattle();
    
    Vector<Unit*> getAllUnits();
};

#endif /* defined(__Monster__Wave__) */
