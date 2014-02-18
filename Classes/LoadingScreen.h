#ifndef __LOADINGSCREEN_H__
#define __LOADINGSCREEN_H__

#include "cocos2d.h"

class LoadingScreen : public cocos2d::CCLayer
{
public:

    virtual bool init(); 

	virtual void onEnter();

	virtual void onExit();
    
    // implement the "static node()" method manually
    CREATE_FUNC(LoadingScreen);
};

#endif // __LOADINGSCREEN_H__
