#include "GameScene.h"
#include "cocos-ext.h"

#include "NodeInit.h"
#include "PhysicsWorld.h"
#include "DebugLayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define ACTOR_Z_ORDER 100
#define DEBUGLAYER_Z_ORDER 50

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

		DebugLayer* debugLayer = DebugLayer::create();
		CC_BREAK_IF(!debugLayer);
		addChild(debugLayer, DEBUGLAYER_Z_ORDER);

		//load scenenodes
		CCNode* pSceneRoot = SceneReader::sharedSceneReader()->createNodeWithSceneFile("DesignResources.json");
		CC_BREAK_IF(!pSceneRoot);
		addChild(pSceneRoot, ACTOR_Z_ORDER);

		CC_BREAK_IF(!NodeInitiator::sharedNodeInitiator()->initAllNodes(pSceneRoot));

	} while (0);

}

void GameScene::onExit()
{
	CCScene::onExit();
	CCLOG("------------------GameScene::onExit()-----------------");
	unscheduleUpdate();
	
	PhysicsWorld::sharedPhysicsWorld()->end();
}

void GameScene::update( float dt )
{
	PhysicsWorld::sharedPhysicsWorld()->update(dt);
}


