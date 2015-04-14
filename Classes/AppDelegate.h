#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

//2734x1536
//2208x1536  用这个分辨率做设计  这个分辨率 比率是  iphone 5，6的 大小能包容下最大的 6 PLus 和  ipad高清版
//
//截取掉高度294得到 2208x1242  就是 iphone 6 plus用的素材
//
//在缩小0.57971014492754到 1280x853 ，所有其他的手机都用这套图
//
//
//出ipad高清的时候  宽度截掉160像素 就有了，2048 x 1536 ，缩50%就有了 1024x768


//for iphone 5, iphone6,iphone 6plus
//1.778,854x480,1280x720,1920x1080,1334x750,1136x640,2208x1242，2734x1536
#define designResolutionSizeA Size(1280,720)//战场大小缩放因子=1280/2208 = 0.57971014492754
#define designResolutionSizeA_HD Size(2208,1242)//战场大小缩放因子=1


//1.677,800x480,1280x766
#define designResolutionSizeB Size(1280,766)//战场大小缩放因子=1280/2208 = 0.57971014492754


//1.6
#define designResolutionSizeC Size(1280,800)//战场大小缩放因子=1280/2208 = 0.57971014492754


//for iphone4
//1.5,1080x720,960x640，1280x853
#define designResolutionSizeD Size(1280,853)//战场大小缩放因子=1280/2208 = 0.57971014492754


//1.333,for ipad，
#define designResolutionSizeE Size(1024,768)//战场大小缩放因子=1024/2208 = 0.46376811594203
#define designResolutionSizeE_HD Size(2048,1536)//战场大小缩放因子=2048/2208 = 0.92753623188406

/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by Director.
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();
    
    float scaleFactory;

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

