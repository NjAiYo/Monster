//
//  LoadScene.h
//  BGT
//
//  Created by John Running on 15/2/28.
//
//

#ifndef __BGT__LoadScene__
#define __BGT__LoadScene__

#include "cocos2d.h"
#include <spine/spine-cocos2dx.h>
USING_NS_CC;

class LoadScene : public cocos2d::Layer
{
private:
    float	total;
    float	imagesLoaded;
    std::vector<std::string> textureNames;
    void imageLoaded(Texture2D* image);
    ProgressTimer *mathProgressBar;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual ~LoadScene(void);
    // implement the "static create()" method manually
    CREATE_FUNC(LoadScene);
};
#endif /* defined(__BGT__LoadScene__) */
