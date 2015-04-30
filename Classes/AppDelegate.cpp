#include "AppDelegate.h"
#include "LoadScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    // Set the design resolution
    Size winSize = director->getWinSize();
    float ratio = winSize.width/winSize.height;
    scaleFactory = 1;
    if (ratio > 1.73) {//1.78
        if(winSize.width > 1600){
            glview->setDesignResolutionSize(designResolutionSizeA_HD.width, designResolutionSizeA_HD.height, ResolutionPolicy::EXACT_FIT);
            scaleFactory = 1.0;
            FileUtils::getInstance()->addSearchPath("resHD");
        }else{
            glview->setDesignResolutionSize(designResolutionSizeA.width, designResolutionSizeA.height, ResolutionPolicy::EXACT_FIT);
            scaleFactory = 1280.0/2208.0;
            FileUtils::getInstance()->addSearchPath("res");
        }
    }else if (ratio > 1.63){//1.67
        glview->setDesignResolutionSize(designResolutionSizeB.width, designResolutionSizeB.height, ResolutionPolicy::EXACT_FIT);
        scaleFactory = 1280.0/2208.0;
        FileUtils::getInstance()->addSearchPath("res");
    }else if (ratio > 1.55){
        glview->setDesignResolutionSize(designResolutionSizeC.width, designResolutionSizeC.height, ResolutionPolicy::EXACT_FIT);
        scaleFactory = 1280.0/2208.0;
        FileUtils::getInstance()->addSearchPath("res");
    }else if (ratio > 1.45){
        glview->setDesignResolutionSize(designResolutionSizeD.width, designResolutionSizeD.height, ResolutionPolicy::EXACT_FIT);
        scaleFactory = 1280.0/2208.0;
        FileUtils::getInstance()->addSearchPath("res");
    }else{//ipad
        if(winSize.width > 1024){
            glview->setDesignResolutionSize(designResolutionSizeE_HD.width, designResolutionSizeE_HD.height, ResolutionPolicy::EXACT_FIT);
            scaleFactory = 2048.0/2208.0;
            FileUtils::getInstance()->addSearchPath("resIpadHD");
        }else{
            glview->setDesignResolutionSize(designResolutionSizeE.width, designResolutionSizeE.height, ResolutionPolicy::EXACT_FIT);
            scaleFactory = 1024.0/2208.0;
            FileUtils::getInstance()->addSearchPath("resIpad");
        }
    }
    //glview->setContentScaleFactor(scaleFactory);
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = LoadScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
