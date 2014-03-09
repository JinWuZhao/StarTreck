#include "PhysicsWorld.h"

USING_NS_CC;

static PhysicsWorld*	_sharedPhysicsWorld = NULL;

PhysicsWorld::PhysicsWorld( void )
	: CCObject(),
	m_pB2World(NULL), 
	m_nPTM_RATIO(5.f),
	m_nMTP_RATIO(1.f/m_nPTM_RATIO),
	m_bIsActive(false), 
	m_nGConst(0.1f),
	m_nMaxBodyNum(50)
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

	for (int i = 0; i < m_nMaxBodyNum; i++)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.active = false;
		b2Body* pBody = m_pB2World->CreateBody(&bodyDef);
		m_BackupBodyList.push_back(pBody);
	}

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
	m_DynamicBodyList.clear();
	m_BackupBodyList.clear();
	CC_SAFE_DELETE(m_pB2World);
}

void PhysicsWorld::addToDynamicList(b2Body* pBody)
{
	if (pBody->GetType() == b2_dynamicBody)
	{
		m_DynamicBodyList.push_back(pBody);
	}
}

void PhysicsWorld::getDynamicList(std::list<b2Body*>& bodyList)
{
	bodyList = m_DynamicBodyList;
}

void PhysicsWorld::removeFromDynamicList(b2Body* pBody)
{
	m_DynamicBodyList.remove(pBody);
}

int PhysicsWorld::getBackupBodyCount()
{
	return m_BackupBodyList.size();
}

b2Body* PhysicsWorld::getNewBody(const b2BodyDef& def)
{
	if (m_BackupBodyList.size())
	{
		b2Body* pNewBody = m_BackupBodyList.front();
		m_BackupBodyList.pop_front();

		pNewBody->SetAngularVelocity(def.angularVelocity);
		pNewBody->SetLinearVelocity(def.linearVelocity);
		pNewBody->SetTransform(def.position,def.angle);
		pNewBody->SetType(def.type);
		pNewBody->SetUserData(def.userData);
		pNewBody->SetActive(def.active);

		return pNewBody;
	}
	return NULL;
}

void PhysicsWorld::collectBody(b2Body* pOldBody)
{
	if (pOldBody)
	{
		pOldBody->SetActive(false);
		b2Fixture* fixtureList = pOldBody->GetFixtureList();
		for (; fixtureList->GetNext() != NULL; fixtureList = fixtureList->GetNext())
		{
			pOldBody->DestroyFixture(fixtureList);
		}
		m_BackupBodyList.push_back(pOldBody);
	}
}
