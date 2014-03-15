#include "PhysicsWorld.h"
#include "GlobalDefine.h"

USING_NS_CC;

static PhysicsWorld*	_sharedPhysicsWorld = NULL;

PhysicsWorld::PhysicsWorld( void )
	: CCObject(),
	m_pB2World(NULL), 
	m_nPTM_RATIO(GMCFG_PTMRATIO),
	m_nMTP_RATIO(1.f/m_nPTM_RATIO),
	m_bIsActive(false), 
	m_nGConst(GMCFG_GRAVITYCONST),
	m_nMaxBodyNum(GMCFG_MAXBODYNUM)
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
	m_pB2World->SetContactListener(this);
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
	m_ContactEventMap.clear();
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

		//clean fixtures
		b2Fixture* fixtureList = pNewBody->GetFixtureList();
		if (fixtureList)
		{
			for (; fixtureList->GetNext() != NULL; fixtureList = fixtureList->GetNext())
			{
				pNewBody->DestroyFixture(fixtureList);
			}
		}

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
		pOldBody->SetUserData(NULL);
		m_DynamicBodyList.remove(pOldBody);
		m_BackupBodyList.push_back(pOldBody);
		m_ContactEventMap.erase(pOldBody);
	}
}

void PhysicsWorld::BeginContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	CCNode* nodeA = static_cast<CCNode*>(bodyA->GetUserData());
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	CCNode* nodeB = static_cast<CCNode*>(bodyB->GetUserData());
	std::list<ContactEvent> eventList;
	//分发事件
	if (nodeA)
	{
		getEventsByKey(bodyA, eventList);
		for (std::list<ContactEvent>::iterator it = eventList.begin(); it != eventList.end(); it++)
		{
			ContactEvent event = *it;
			if (event.beginContact)
			{
				(event.user->*(event.beginContact))(nodeB);
			}
		}
	}
	if (nodeB)
	{
		getEventsByKey(bodyA, eventList);
		for (std::list<ContactEvent>::iterator it = eventList.begin(); it != eventList.end(); it++)
		{
			ContactEvent event = *it;
			if (event.beginContact)
			{
				(event.user->*(event.beginContact))(nodeA);
			}
		}
	}
}

void PhysicsWorld::EndContact(b2Contact* contact)
{
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	CCNode* nodeA = static_cast<CCNode*>(bodyA->GetUserData());
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	CCNode* nodeB = static_cast<CCNode*>(bodyB->GetUserData());
	std::list<ContactEvent> eventList;
	//分发事件
	if (nodeA)
	{
		getEventsByKey(bodyA, eventList);
		for (std::list<ContactEvent>::iterator it = eventList.begin(); it != eventList.end(); it++)
		{
			ContactEvent event = *it;
			if (event.endContact)
			{
				(event.user->*(event.endContact))(nodeB);
			}
		}
	}
	if (nodeB)
	{
		getEventsByKey(bodyA, eventList);
		for (std::list<ContactEvent>::iterator it = eventList.begin(); it != eventList.end(); it++)
		{
			ContactEvent event = *it;
			if (event.endContact)
			{
				(event.user->*(event.endContact))(nodeA);
			}
		}
	}
}

void PhysicsWorld::registerBeginContactEvent(b2Body* owner, cocos2d::CCObject* user, SEL_CONTACT sel)
{
	CC_ASSERT(owner && user && sel);
	ContactEvent event;
	event.owner = owner;
	event.user = user;
	event.beginContact = sel;
	m_ContactEventMap.insert(std::pair<b2Body*, ContactEvent>(owner, event));
}

void PhysicsWorld::registerEndContactEvent(b2Body* owner, cocos2d::CCObject* user, SEL_CONTACT sel)
{
	CC_ASSERT(owner && user && sel);
	ContactEvent event;
	event.owner = owner;
	event.user = user;
	event.endContact = sel;
	m_ContactEventMap.insert(std::pair<b2Body*, ContactEvent>(owner, event));
}

void PhysicsWorld::getEventsByKey(b2Body* key, std::list<ContactEvent>& eventList)
{
	eventList.clear();

	for (std::multimap<b2Body*, ContactEvent>::iterator it = m_ContactEventMap.begin(); it != m_ContactEventMap.end(); it++)
	{
		if ((*it).first == key)
		{
			eventList.push_back((*it).second);
		}
	}
}
