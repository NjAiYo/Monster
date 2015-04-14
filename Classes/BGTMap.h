//
//  BGTMap.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__BGTMap__
#define __BGT__BGTMap__

#include "cocos2d.h"


USING_NS_CC;

class BGTMap : public cocos2d::Layer
{
private:
    unsigned int currentLevel;
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    BGTMap();
    // implement the "static create()" method manually
    CREATE_FUNC(BGTMap);

};

#endif /* defined(__BGT__BGTMap__) */
