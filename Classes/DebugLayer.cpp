#include "DebugLayer.h"

#include "NodeInit.h"
#include "PhysicsWorld.h"
#include "GLES-Render.h"

USING_NS_CC;

bool DebugLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	return true;
}

void DebugLayer::onEnter()
{
	CCLayer::onEnter();
	CCLOG("------------------DebugLayer::onEnter()-----------------");

	m_pDebugDraw = new GLESDebugDraw(PhysicsWorld::sharedPhysicsWorld()->getRatio());
}

void DebugLayer::onExit()
{
	CCLayer::onExit();
	CCLOG("------------------DebugLayer::onExit()-----------------");

	CC_SAFE_DELETE(m_pDebugDraw);
}

void DebugLayer::draw()
{
	CCLayer::draw();
	m_pDebugDraw->DrawSolidCircle(b2Vec2(30, 50), 10, b2Vec2(0, 0), b2Color(255, 0, 0));
}


