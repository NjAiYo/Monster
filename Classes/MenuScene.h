//
//  MenuScene.h
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#ifndef __BGT__MenuScene__
#define __BGT__MenuScene__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
private:
    void playCallback(Ref* sender);
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif /* defined(__BGT__MenuScene__) */
