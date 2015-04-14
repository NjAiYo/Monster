//
//  UILayer.cpp
//  BGT
//
//  Created by John Running on 15/3/3.
//
//

#include "UILayer.h"
#include "AppDelegate.h"
#include "BGTWorld.h"
#include "GameScene.h"

UILayer::UILayer()
{
    
}

bool UILayer::initWithGameScene(GameScene *gs)
{
    if (!Layer::init()) {
        return false;
    }
    gameScene = gs;
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    gunIcon = Sprite::create("gunBt.png");
    addChild(gunIcon);
    gunIcon->setPosition(200*scaleFactory, 200*scaleFactory);
    
    knifeIcon = Sprite::create("knifeBt.png");
    addChild(knifeIcon);
    knifeIcon->setPosition(200*scaleFactory, 200*scaleFactory);
    
    gunIcon->setVisible(false);
    
    
    // Register Touch Event
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(UILayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(UILayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(UILayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(UILayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool UILayer::onTouchBegan(Touch* touch, Event* event)
{
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    Vec2 pos = touch->getLocation();
    Rect rect = Rect(knifeIcon->getPositionX()-200*scaleFactory/2, knifeIcon->getPositionY()-200*scaleFactory/2, 200*scaleFactory, 200*scaleFactory);
    if (rect.containsPoint(pos)) {
        knifeIcon->setVisible(!knifeIcon->isVisible());
        gunIcon->setVisible(!gunIcon->isVisible());
        gameScene->getWorld()->toggleWeapon();
        return true;
    }
    
    return false;
}

void UILayer::onTouchMoved(Touch* touch, Event* event)
{

}

void UILayer::onTouchEnded(Touch* touch, Event* event)
{

}

void UILayer::onTouchCancelled(Touch *touch, Event *unused_event)
{

}
