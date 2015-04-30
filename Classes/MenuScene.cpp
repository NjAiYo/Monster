//
//  MenuScene.cpp
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#include "MenuScene.h"
#include "GameScene.h"
#include "AppDelegate.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    ZipUtils::setPvrEncryptionKeyPart(0,0xf858f36b);
    ZipUtils::setPvrEncryptionKeyPart(1,0xcc54eed0);
    ZipUtils::setPvrEncryptionKeyPart(2,0xdbf1274e);
    ZipUtils::setPvrEncryptionKeyPart(3,0xf3d29164);
    
    
    SpriteFrameCache *ccsfc = SpriteFrameCache::getInstance();
    ccsfc->addSpriteFramesWithFile("MainMenuScene.plist");

    Size size = Director::getInstance()->getWinSize();
    Sprite *sprite = Sprite::createWithSpriteFrameName("playButton.png");
    Sprite *sprite1 = Sprite::createWithSpriteFrameName("playButton.png");
    sprite1->setScale(1.1);
    Size spriteSize = sprite->getContentSize();
    sprite1->setPosition(Point(-spriteSize.width*0.1/2,-spriteSize.height*0.1/2));
    
    MenuItemSprite *playItem = MenuItemSprite::create(sprite,sprite1,CC_CALLBACK_1(MenuScene::playCallback, this));
    
    Menu *playMenu = Menu::create(playItem,NULL);
    playMenu->setPosition(size.width/2,size.height/2);
    addChild(playMenu, 1);
    
    AppDelegate *app = (AppDelegate*)Application::getInstance();
    float scaleFactory = app->scaleFactory;
    
    
//    spAtlas* atlas = spAtlas_createFromFile( "skeleton.atlas", 0);
//    SkeletonAnimation *skeletonNode = SkeletonAnimation::createWithFile("skeleton.json", atlas, 0.45f * scaleFactory);
//    
//    //skeletonNode->setAnimation(0, "walk", true);
//    //        spine::SkeletonAnimation *skeletonNode = SkeletonAnimation::createWithFile("hero.json", "hero.atlas", 0.6f);
//    skeletonNode->setAnimation(0, "daiji", true);
//    skeletonNode->setPosition(0, 0);
//    addChild(skeletonNode);
    return true;
}

void MenuScene::playCallback(Ref* sender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createSceneWithLevel(0)));
//    Director::getInstance()->replaceScene(TransitionSlideInT::create(1, GameScene::createSceneWithLevel(0)));
}

