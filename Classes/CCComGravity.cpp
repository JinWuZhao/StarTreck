#include "CCComGravity.h"
#include "Box2D.h"
#include "cocos-ext.h"
#include "CCComRigidBody.h"
#include "PhysicsWorld.h"

USING_NS_CC;
USING_NS_CC_EXT;

#define MIN_GRAVITY 1.0f

CCComGravity::CCComGravity()
: CCComponent(),
m_nRadius(1.f), m_nDensity(1.f), m_nMass(0.f)
{
}


CCComGravity::~CCComGravity()
{
}

CCComGravity* CCComGravity::create(void)
{
	CCComGravity * pRet = new CCComGravity();
	if (pRet != NULL && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CCComGravity::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComGravity");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComGravity::onEnter()
{
	CCLOG("CCComGravity::onEnter()");

	CCComAttribute* comAttribute = static_cast<CCComAttribute*>(m_pOwner->getComponent("CCComAttribute"));
	setDensity(comAttribute->getFloat("Density", 1.0f));
}

void CCComGravity::onExit()
{
	CCLOG("CCComGravity::onExit()");
}

void CCComGravity::update(float delta)
{
	CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
	CC_ASSERT(comRigidBody);
	b2Body* pOwnerBody = comRigidBody->getBody();
	CC_ASSERT(pOwnerBody);

	std::list<b2Body*> bodyList;
	PhysicsWorld::sharedPhysicsWorld()->getDynamicList(bodyList);
	//遍历列表中的body，对范围内的目标施加引力
	std::list<b2Body*>::iterator bodyIt;
	for (bodyIt = bodyList.begin(); bodyIt != bodyList.end(); bodyIt++)
	{
		if ((*bodyIt)->IsActive() && (*bodyIt)->GetType() == b2_dynamicBody)
		{
			b2Vec2 disVec = pOwnerBody->GetPosition() - (*bodyIt)->GetPosition();
			float FGScalar = m_nMass * (*bodyIt)->GetMass() / disVec.LengthSquared() * PhysicsWorld::sharedPhysicsWorld()->getGConst();
			if (FGScalar > MIN_GRAVITY)
			{
				disVec.Normalize();
				b2Vec2 FG(FGScalar / disVec.x, FGScalar/ disVec.y);
				(*bodyIt)->ApplyForceToCenter(FG);
			}
		}
	}
}

float CCComGravity::computeMass(void)
{
	CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
	CC_ASSERT(comRigidBody && comRigidBody->getBody());
	b2Shape* pShape = comRigidBody->getBody()->GetFixtureList()->GetShape();
	CC_ASSERT(pShape && pShape->GetType() == b2Shape::e_circle);
	b2CircleShape* pCircleShape = static_cast<b2CircleShape*>(pShape);
	b2MassData massData;
	pCircleShape->ComputeMass(&massData, m_nDensity);
	m_nMass = massData.mass;
	return m_nMass;
}

float CCComGravity::computeRadius(void)
{
	m_nRadius = m_nMass * PhysicsWorld::sharedPhysicsWorld()->getGConst() / MIN_GRAVITY;
	return m_nRadius;
}

void CCComGravity::setDensity(float density)
{
	m_nDensity = density;
	computeMass();
	computeRadius();
}
