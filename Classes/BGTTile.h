//
//  BGTTile.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__BGTTile__
#define __BGT__BGTTile__

#include "cocos2d.h"

class BGTTile : public cocos2d::Ref
{
    CC_SYNTHESIZE(unsigned int, _col, Col);
    CC_SYNTHESIZE(unsigned int, _row, Row);
    
public:
    BGTTile();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(BGTTile);
    
    
};

#endif /* defined(__BGT__BGTTile__) */
