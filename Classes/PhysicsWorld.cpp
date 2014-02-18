#include "PhysicsWorld.h"

USING_NS_CC;

static PhysicsWorld*	_sharedPhysicsWorld = NULL;

PhysicsWorld::PhysicsWorld( void )
	: CCObject(),
	m_pB2World(NULL), m_nPTM_RATIO(10), m_bIsActive(false)
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
	CC_SAFE_DELETE(m_pB2World);
}
