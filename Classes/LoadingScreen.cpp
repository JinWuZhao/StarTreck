#include "LoadingScreen.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool LoadingScreen::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    return true;
}

void LoadingScreen::onEnter()
{
	CCLayer::onEnter();
}

void LoadingScreen::onExit()
{
	CCLayer::onExit();
}
