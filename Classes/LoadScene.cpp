//
//  LoadScene.cpp
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#include "LoadScene.h"
#include "MenuScene.h"
#include <SimpleAudioEngine.h>

using namespace spine;

Scene* LoadScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

LoadScene::~LoadScene(void)
{

}

// on "init" you need to initialize your instance
bool LoadScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    
    textureNames.push_back("gamebg.jpg");
    textureNames.push_back("rope.png");
    textureNames.push_back("stone.png");
    imagesLoaded = 0;
    total = textureNames.size();
    
    
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("dao_1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("jq.mp3");
    
    for(int i = 0; i < total; i++){
        std::string name = textureNames.at(i);
        Director::getInstance()->getTextureCache()->addImageAsync(name.c_str(), CC_CALLBACK_1(LoadScene::imageLoaded,this));
    }
    return true;
}

void LoadScene::imageLoaded(Texture2D* image)
{
    imagesLoaded++;
    //mathProgressBar->setPercentage(imagesLoaded/total * 100);
    if( total == imagesLoaded )
        Director::getInstance()->replaceScene(MenuScene::createScene());
}
