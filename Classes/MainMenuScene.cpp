#include "MainMenuScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    return true;
}

void MainMenu::onEnter()
{
	CCLayer::onEnter();
}

void MainMenu::onExit()
{
	CCLayer::onExit();
}
