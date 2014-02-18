#include "CCComRigidBody.h"
#include "PhysicsWorld.h"

USING_NS_CC;

CCComRigidBody::CCComRigidBody( void )
	: CCComponent(),
	m_pBody(NULL)
{
}

CCComRigidBody::~CCComRigidBody( void )
{
}

CCComRigidBody* CCComRigidBody::create( void )
{
	CCComRigidBody * pRet = new CCComRigidBody();
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

bool CCComRigidBody::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComRigidBody");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComRigidBody::onEnter()
{
	CCLOG("CCComRigidBody::onEnter()");
}

void CCComRigidBody::onExit()
{
	CCLOG("CCComRigidBody::onExit()");
	if (PhysicsWorld::sharedPhysicsWorld()->getIsActive())
	{
		if (m_pBody)
		{
			PhysicsWorld::sharedPhysicsWorld()->getB2World()->DestroyBody(m_pBody);
		}
	}
	m_pBody = NULL;
}

void CCComRigidBody::update( float delta )
{
	if (m_pBody)
	{
		b2Vec2 pos = m_pBody->GetPosition();
		pos.x /= PhysicsWorld::sharedPhysicsWorld()->getRatio();
		pos.y /= PhysicsWorld::sharedPhysicsWorld()->getRatio();
		m_pOwner->setPosition(pos.x, pos.y);
		m_pOwner->setRotation(m_pBody->GetAngle()*180);
	}
}

b2Body* CCComRigidBody::createBody( const b2BodyDef& bodyDef )
{
	if (!m_pBody)
	{
		m_pBody = PhysicsWorld::sharedPhysicsWorld()->getB2World()->CreateBody(&bodyDef);
	}
	return m_pBody;
}

b2Fixture* CCComRigidBody::createFixture( const b2FixtureDef& fixtureDef )
{
	b2Fixture* pFixture = NULL;
	if (m_pBody)
	{
		pFixture = m_pBody->CreateFixture(&fixtureDef);
	}
	return pFixture;
}

void CCComRigidBody::setVisible( bool visible )
{
	m_pBody->SetActive(visible);
	m_pOwner->setVisible(visible);
}

void CCComRigidBody::applyForceToCenter( const b2Vec2& force )
{
	m_pBody->ApplyForceToCenter(force);
}

void CCComRigidBody::applyForce( const b2Vec2& force, const b2Vec2& point )
{
	m_pBody->ApplyForce(force, point);
}

void CCComRigidBody::applyTorque( float torque )
{
	m_pBody->ApplyTorque(torque);
}