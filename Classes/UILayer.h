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
#include "GameManager.h"

USING_NS_CC;

class GameScene;

class UILayer : public cocos2d::Layer
{
private:
    GameScene *gameScene;
    Sprite *knifeIcon;
    Sprite *gunIcon;
    Layer *hudLayer;
    LayerColor *winLayer;
    LayerColor *failedLayer;
    LayerColor *pausedLayer;
    Label *scorelabel;
    Label *playerLevelLabel;
    Label *coinLabel;
    
    GameManager *gameManager;
    Player *player;
    Sprite *enegyBar;
    ProgressTimer *enegyProgressBar;
    
    Sprite *lifeBar;
    ProgressTimer *lifeProgressBar;
    
    void restartCallback(Ref* sender);
    void nextLevelCallback(Ref* sender);
    void pauseCallback(Ref* sender);
    void resumeCallback(Ref* sender);
    
    
public:
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithGameScene(GameScene *gs);
    UILayer();
    // implement the "static create()" method manually
    CREATE_FUNC(UILayer);
    
    void gameEnd(bool isWin);
    void gameStart();
    void update(float dt);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
};

#endif /* defined(__BGT__UILayer__) */
