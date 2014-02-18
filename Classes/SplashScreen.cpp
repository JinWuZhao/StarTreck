#include "SplashScreen.h"

USING_NS_CC;

CCScene* SplashScreen::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SplashScreen *layer = SplashScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScreen::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	CCLOG("------------------GameScene::init()-----------------");

    return true;
}

void SplashScreen::onEnter()
{
	CCLayer::onEnter();

	CCLOG("------------------GameScene::onEnter()-----------------");
}

void SplashScreen::onExit()
{
	CCLayer::onExit();

	CCLOG("------------------GameScene::onExit()-----------------");
}
