#include "CCComRigidBody.h"
#include "PhysicsWorld.h"

USING_NS_CC;

CCComRigidBody::CCComRigidBody( void )
	: CCComponent(),
	m_pBody(NULL), m_bIsDynamic(false)
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
			if (m_bIsDynamic)
			{
				PhysicsWorld::sharedPhysicsWorld()->removeFromDynamicList(m_pBody);
			}
			PhysicsWorld::sharedPhysicsWorld()->collectBody(m_pBody);
		}
	}
	m_pBody = NULL;
}

void CCComRigidBody::update( float delta )
{
	if (m_pBody)
	{
		b2Vec2 pos = m_pBody->GetPosition();
		pos.x *= PhysicsWorld::sharedPhysicsWorld()->getM2pRatio();
		pos.y *= PhysicsWorld::sharedPhysicsWorld()->getM2pRatio();
		m_pOwner->setPosition(pos.x, pos.y);
		m_pOwner->setRotation(m_pBody->GetAngle()*180);
	}
}

b2Body* CCComRigidBody::createBody(const b2BodyDef& bodyDef, bool bBackup)
{
	if (!m_pBody)
	{
		m_pBody = PhysicsWorld::sharedPhysicsWorld()->getNewBody(bodyDef);
		m_pBody->SetUserData((void*)m_pOwner);
		if (bBackup)
		{
			m_bIsDynamic = true;
			PhysicsWorld::sharedPhysicsWorld()->addToDynamicList(m_pBody);
		}
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

cocos2d::CCPoint CCComRigidBody::getVelocity(void)
{
	b2Vec2 velocity = m_pBody->GetLinearVelocity();
	return ccp(velocity.x, velocity.y)*(PhysicsWorld::sharedPhysicsWorld()->getM2pRatio());
}
