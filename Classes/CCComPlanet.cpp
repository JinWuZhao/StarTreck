#include "CCComPlanet.h"
#include "Box2D.h"
#include "cocos-ext.h"
#include "PhysicsWorld.h"
#include "CCComRigidBody.h"
#include "CCComGravity.h"
#include "NodeInit.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCComPlanet::CCComPlanet()
: CCComponent(),
m_pCenterPlanet(NULL)
{
}


CCComPlanet::~CCComPlanet()
{
}

CCComPlanet* CCComPlanet::create(void)
{
	CCComPlanet * pRet = new CCComPlanet();
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

bool CCComPlanet::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComPlanet");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComPlanet::onEnter()
{
	CCLOG("CCComPlanet::onEnter()");

	//get comRigidbody
	CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
	CC_ASSERT(comRigidBody);

	//get bounding box
	CCComRender* comRender = static_cast<CCComRender*>(m_pOwner->getComponent("CCArmature"));
	CC_ASSERT(comRender);
	CCArmature* pArmature = static_cast<CCArmature*>(comRender->getNode());
	CC_ASSERT(pArmature);
	CCRect bbox = pArmature->boundingBox();

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	float ratio = PhysicsWorld::sharedPhysicsWorld()->getP2mRatio();
	CCPoint pos = m_pOwner->getPosition();
	bodyDef.position = b2Vec2(ratio*pos.x, ratio*pos.y);
	comRigidBody->createBody(bodyDef);

	//get comAttribute and set center planet
	CCComAttribute* comAttribute = static_cast<CCComAttribute*>(m_pOwner->getComponent("CCComAttribute"));
	CC_ASSERT(comAttribute);
	CCNode* rootNode = NodeInitiator::sharedNodeInitiator()->getRootNode();
	CC_ASSERT(rootNode);
	m_pCenterPlanet = rootNode->getChildByTag(comAttribute->getInt("CenterNodeTag", -10000));

	//create fixture
	b2CircleShape	shape;
	shape.m_radius = bbox.size.width / 2 * ratio * m_pOwner->getScale();
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = comAttribute->getFloat("Friction", 1.0f);
	fixtureDef.restitution = comAttribute->getFloat("Restitution", 0.2f);
	comRigidBody->createFixture(fixtureDef);
}

void CCComPlanet::onExit()
{
	CCLOG("CCComPlanet::onExit()");
}

void CCComPlanet::update(float delta)
{
	//使该星球围绕中心星球公转

	if (m_pCenterPlanet)
	{
		//get rigidbody
		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		b2Body* pOwnerBody = comRigidBody->getBody();
		CC_ASSERT(pOwnerBody);
		comRigidBody = NULL;
		comRigidBody = static_cast<CCComRigidBody*>(m_pCenterPlanet->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		b2Body* pCenterBody = comRigidBody->getBody();
		CC_ASSERT(pCenterBody);

		//get CCComGravity
		CCComGravity* comGravity = static_cast<CCComGravity*>(m_pOwner->getComponent("CCComGravity"));
		CC_ASSERT(comGravity);
		float ownerMass = comGravity->getMass();
		comGravity = NULL;
		comGravity = static_cast<CCComGravity*>(m_pCenterPlanet->getComponent("CCComGravity"));
		CC_ASSERT(comGravity);
		float centerMass = comGravity->getMass();

		//Compute the accelerated speed
		b2Vec2 disVec = pCenterBody->GetPosition() - pOwnerBody->GetPosition();
		float FGScalar = ownerMass * centerMass / disVec.LengthSquared() * PhysicsWorld::sharedPhysicsWorld()->getGConst();
		disVec.Normalize();
		b2Vec2 accelSpeed = b2Vec2(FGScalar * disVec.x / ownerMass, FGScalar * disVec.y / ownerMass);

		disVec = pCenterBody->GetPosition() - pOwnerBody->GetPosition();

		//Compute the linear speed scalar
		float speedScalar = sqrtf(sqrtf(accelSpeed.LengthSquared()*disVec.LengthSquared()));

		//Compute the inital speed and apply it.
		b2Vec2 initialLinearVelocity = b2Cross(1.f, -disVec);
		initialLinearVelocity.Normalize();
		initialLinearVelocity = speedScalar * initialLinearVelocity;
		pOwnerBody->SetLinearVelocity(initialLinearVelocity);
	}
}
