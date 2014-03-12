#include "DebugLayer.h"

#include "NodeInit.h"
#include "PhysicsWorld.h"
#include "GLES-Render.h"
#include "Camera.h"
#include "VisibleRect.h"

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

	m_pDebugDraw = new GLESDebugDraw(PhysicsWorld::sharedPhysicsWorld()->getM2pRatio());
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
	b2Body* pBodyList = PhysicsWorld::sharedPhysicsWorld()->getB2World()->GetBodyList();
	for (int i = 0; i < PhysicsWorld::sharedPhysicsWorld()->getB2World()->GetBodyCount(); i++)
	{
		if (pBodyList->GetFixtureList())
		{
			b2Vec2 pos = pBodyList->GetPosition();
			b2Shape* pShape = pBodyList->GetFixtureList()->GetShape();
			if (pShape->GetType() == b2Shape::e_circle)
			{
				float radius = static_cast<b2CircleShape*>(pShape)->m_radius;
				CCPoint viewPos = Camera::sharedCamera()->getPosition();
				CCPoint presentPos = (VisibleRect::center() - viewPos)*(PhysicsWorld::sharedPhysicsWorld()->getP2mRatio()) + ccp(pos.x, pos.y);
				m_pDebugDraw->DrawCircle(b2Vec2(presentPos.x, presentPos.y), radius, b2Color(255, 0, 0));
			}
		}
		pBodyList = pBodyList->GetNext();
	}
	
}


