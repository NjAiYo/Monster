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



Scene* GameScene::createSceneWithLevel(unsigned int level)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = new GameScene();
    layer->initWithLevel(level);
    // add layer as a child to scene
    scene->addChild(layer);
    layer->release();
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::initWithLevel(unsigned int level)
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    SpriteFrameCache *ccsfc = SpriteFrameCache::getInstance();
    ccsfc->addSpriteFramesWithFile("GameScene.plist");
    
    currentLevel = level;
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
    

    
    setLevel(currentLevel);
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
    scheduleUpdate();
    world->startGame();
    uiLayer->gameStart();
    
    state = GameStateGaming;
}

void GameScene::restartGame()
{
    //删掉之前所有的entitymanager里的entity
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
    world->pauseGame();
    pausedNodes = Director::getInstance()->getActionManager()->pauseAllRunningActions();
    Director::getInstance()->getScheduler();
}

void GameScene::resumeGame()
{
    Director::getInstance()->getActionManager()->resumeTargets(pausedNodes);
    state = GameStateGaming;
    world->resumeGame();
}

void GameScene::gameEnd(bool isWin)
{
    state = GameStateEnded;
    uiLayer->gameEnd(isWin);
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
        uiLayer->update(dt);
    }
}
