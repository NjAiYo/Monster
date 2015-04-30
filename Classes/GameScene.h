//
//  GameScene.h
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#ifndef __BGT__GameScene__
#define __BGT__GameScene__

#include "cocos2d.h"
#include "BGTWorld.h"
#include "Utils.h"
#include "UILayer.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
private:
    BGTWorld *world;
    UILayer *uiLayer;
    unsigned int currentLevel;
    GameState state;
    
    Vector<Node*> pausedNodes;
    
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createSceneWithLevel(unsigned int level);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool initWithLevel(unsigned int level);
    
    GameState getState();
    
    BGTWorld* getWorld();
    
    void createWorld();
    
    void startGame();
    void restartGame();
    void nextLevel();
    void setLevel(unsigned value);
    void pauseGame();
    void resumeGame();
    void gameEnd(bool isWin);
    
    void update(float dt);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExitTransitionDidStart() override;
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchCancelled(Touch *touch, Event *unused_event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* defined(__BGT__GameScene__) */
