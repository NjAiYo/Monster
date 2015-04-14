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
    
public:
    Troop();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(){ return true;};
    
    // implement the "static create()" method manually
    CREATE_FUNC(Troop);
    
    Vector<Unit*> units;
};

#endif /* defined(__BGT__Troop__) */
