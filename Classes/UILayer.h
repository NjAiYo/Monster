//
//  UILayer.h
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#ifndef __BGT__UILayer__
#define __BGT__UILayer__

#include "cocos2d.h"

USING_NS_CC;

class GameScene;

class UILayer : public cocos2d::Layer
{
private:
    GameScene *gameScene;
    Sprite *knifeIcon;
    Sprite *gunIcon;
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithGameScene(GameScene *gs);
    UILayer();
    // implement the "static create()" method manually
    CREATE_FUNC(UILayer);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif /* defined(__BGT__UILayer__) */
