#include "GameScene.h"
#include "cocos-ext.h"

#include "NodeInit.h"
#include "PhysicsWorld.h"
#include "DebugLayer.h"
#include "StageManager.h"
#include "Camera.h"
#include "GlobalDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

void GameScene::onEnter()
{
	CCScene::onEnter();
	CCLOG("------------------GameScene::onEnter()-----------------");

	//open update schedule
	scheduleUpdate();

	do 
	{
		//create Physics World
		CC_BREAK_IF(!PhysicsWorld::sharedPhysicsWorld()->init());

#if GMCFG_SHOWDEBUGINFO
		DebugLayer* debugLayer = DebugLayer::create();
		CC_BREAK_IF(!debugLayer);
		addChild(debugLayer, ZORDER_DEBUGLAYER);
#endif

		//load scenenodes
		StageManager* stageMgr = StageManager::sharedStageManager();
		std::vector<StageInfo> stageData;
		CC_BREAK_IF(!stageMgr->readStageData(stageData));
		CCNode* pSceneRoot = stageMgr->loadStage(stageData[0].name);
		CC_BREAK_IF(!pSceneRoot);
		addChild(pSceneRoot, ZORDER_ACTORLAYER);

		//camera
		CCNode* pCameraActor = CCNode::create();
		pCameraActor->setTag(TAG_CAMERAACTOR);
		pSceneRoot->addChild(pCameraActor);

		//init nodes
		CC_BREAK_IF(!NodeInitiator::sharedNodeInitiator()->initAllNodes(pSceneRoot));

	} while (0);

}

void GameScene::onExit()
{
	CCLOG("------------------GameScene::onExit()-----------------");
	PhysicsWorld::sharedPhysicsWorld()->end();

	CCScene::onExit();
}

void GameScene::update( float dt )
{
	PhysicsWorld::sharedPhysicsWorld()->update(dt);
}


