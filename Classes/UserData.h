//
//  UserData.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__UserData__
#define __BGT__UserData__

#include "cocos2d.h"
#include "sqlite3.h"

USING_NS_CC;

class UserData : public cocos2d::Ref
{
private:
    sqlite3 *pDB;
    
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    UserData();
    
};

#endif /* defined(__BGT__UserData__) */
