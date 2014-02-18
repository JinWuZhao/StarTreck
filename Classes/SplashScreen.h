#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include "cocos2d.h"

class SplashScreen : public cocos2d::CCLayer
{
public:

	static cocos2d::CCScene* scene();

    virtual bool init();

	virtual void onEnter();

	virtual void onExit();
    
    // implement the "static node()" method manually
    CREATE_FUNC(SplashScreen);
};

#endif // __SPLASHSCREEN_H__
