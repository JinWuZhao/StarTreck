#include "PhysicsWorld.h"

USING_NS_CC;

static PhysicsWorld*	_sharedPhysicsWorld = NULL;

PhysicsWorld::PhysicsWorld( void )
	: CCObject(),
	m_pB2World(NULL), 
	m_nPTM_RATIO(5.f),
	m_nMTP_RATIO(1.f/m_nPTM_RATIO),
	m_bIsActive(false), 
	m_nGConst(0.1f)
{

}

PhysicsWorld::~PhysicsWorld( void )
{

}

PhysicsWorld* PhysicsWorld::sharedPhysicsWorld()
{
	if (!_sharedPhysicsWorld)
	{
		_sharedPhysicsWorld = new PhysicsWorld();
	}
	return _sharedPhysicsWorld;
}

bool PhysicsWorld::init()
{
	m_pB2World = new b2World(b2Vec2(0.f, 0.f));
	if (!m_pB2World)
	{
		return false;
	}
	m_bIsActive = true;
	return true;
}

void PhysicsWorld::update( float dt )
{
	int32 velocityIterations = 10;
	int32 positionIterations = 8;
	m_pB2World->Step(dt, velocityIterations, positionIterations);
}

void PhysicsWorld::end()
{
	m_bIsActive = false;
	m_BodyList.clear();
	CC_SAFE_DELETE(m_pB2World);
}

void PhysicsWorld::addToBackupList(b2Body* pBody)
{
	if (pBody->GetType() == b2_dynamicBody)
	{
		m_BodyList.push_back(pBody);
	}
}

void PhysicsWorld::getBackupList(std::list<b2Body*>& bodyList)
{
	bodyList = m_BodyList;
}

void PhysicsWorld::removeFromBackupList(b2Body* pBody)
{
	m_BodyList.remove(pBody);
}
