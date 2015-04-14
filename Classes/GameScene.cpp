//
//  GameScene.cpp
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#include "GameScene.h"
#include "BGTWall.h"
#include "AppDelegate.h"



Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    currentLevel = 0;
    state = GameStateReady;
    
    Size size = Director::getInstance()->getWinSize();
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    //log("size:%f,%f,%f",size.width,size.height,scaleFactory);
    
    world = new BGTWorld();
    world->initWithGameScene(this);
    addChild(world);
    world->release();
    
    uiLayer = new UILayer();
    uiLayer->initWithGameScene(this);
    addChild(uiLayer);
    uiLayer->release();
    
    return true;
}

void GameScene::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    startGame();
}

void GameScene::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}

void GameScene::onEnter()
{
    Layer::onEnter();
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void GameScene::onExit()
{
    Layer::onExit();
}

BGTWorld* GameScene::getWorld()
{
    return world;
}

GameState GameScene::getState()
{
    return state;
}

void GameScene::createWorld()
{
    world->createWorld(currentLevel);
}

void GameScene::startGame()
{
    setLevel(currentLevel);
    scheduleUpdate();
    state = GameStateGaming;
}

void GameScene::restartGame()
{
    
}

void GameScene::nextLevel()
{
    setLevel(currentLevel+1);
}

void GameScene::setLevel(unsigned value)
{
    currentLevel = value;
    createWorld();
}

void GameScene::pauseGame()
{
    state = GameStatePaused;
    pausedNodes = Director::getInstance()->getActionManager()->pauseAllRunningActions();
    Director::getInstance()->getScheduler();
}

void GameScene::resumeGame()
{
    Director::getInstance()->getActionManager()->resumeTargets(pausedNodes);
    state = GameStateGaming;
}

void GameScene::gameEnd()
{
    state = GameStateEnded;
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    if (state == GameStateGaming) {
        world->onTouchBegan(touch,event);
    }
    return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    if (state == GameStateGaming) {
        world->onTouchMoved(touch,event);
    }
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    if (state == GameStateGaming) {
        world->onTouchEnded(touch,event);
    }
}

void GameScene::onTouchCancelled(Touch *touch, Event *unused_event)
{
    if (state == GameStateGaming) {
        world->onTouchCancelled(touch,unused_event);
    }
}

void GameScene::update(float dt)
{
    if (state == GameStateGaming) {
        world->update(dt);
    }
}
