#include "AppDelegate.h"
#include "GlobalDefine.h"
#include "SplashScreen.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

	pEGLView->setDesignResolutionSize(GMCFG_DESIGNRESOLUSION_WIDTH, GMCFG_DESIGNRESOLUSION_HEIGHT, kResolutionNoBorder);

	CCFileUtils* pfileUtils = CCFileUtils::sharedFileUtils();
	pfileUtils->addSearchPath(PATH_FONT_ROOT);
	pfileUtils->addSearchPath(PATH_IMAGE_ROOT);
	pfileUtils->addSearchPath(PATH_STAGE_ROOT);
	pfileUtils->addSearchPath(PATH_UI_ROOT);

    // create a scene. it's an autorelease object
    CCScene *pSplash = SplashScreen::scene();
	
    // run
	pDirector->runWithScene(pSplash);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
