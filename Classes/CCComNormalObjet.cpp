#include "CCComNormalObjet.h"
#include "Box2D.h"
#include "cocos-ext.h"
#include "CCComRigidBody.h"
#include "PhysicsWorld.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCComNormalObjet::CCComNormalObjet()
: CCComponent()
{
}


CCComNormalObjet::~CCComNormalObjet()
{
}

CCComNormalObjet* CCComNormalObjet::create(void)
{
	CCComNormalObjet* pRet = new CCComNormalObjet();
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

bool CCComNormalObjet::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComNormalObjet");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComNormalObjet::onEnter()
{
	CCLOG("CCComNormalObjet::onEnter()");

	//get comRigidbody
	CCComRigidBody* comRigidBody = CCComRigidBody::create();
	CC_ASSERT(comRigidBody);

	//get bounding box
	CCComRender* comRender = static_cast<CCComRender*>(m_pOwner->getComponent("CCArmature"));
	CC_ASSERT(comRender);
	CCArmature* pArmature = static_cast<CCArmature*>(comRender->getNode());
	CC_ASSERT(pArmature);
	CCRect bbox = pArmature->boundingBox();

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	float ratio = PhysicsWorld::sharedPhysicsWorld()->getP2mRatio();
	CCPoint pos = m_pOwner->getPosition();
	bodyDef.position = b2Vec2(ratio*pos.x, ratio*pos.y);
	comRigidBody->createBody(bodyDef);

	//get comAttribute
	CCComAttribute* comAttribute = static_cast<CCComAttribute*>(m_pOwner->getComponent("CCComAttribute"));
	CC_ASSERT(comAttribute);

	//create fixture
	b2CircleShape	shape;
	shape.m_radius = bbox.size.width / 2 * ratio * m_pOwner->getScale();
	b2FixtureDef fixtureDef;
	fixtureDef.density = comAttribute->getFloat("Density", 1.0f);
	fixtureDef.friction = comAttribute->getFloat("Friction", 1.0f);
	fixtureDef.restitution = comAttribute->getFloat("Restitution", 0.2f);
	fixtureDef.shape = &shape;
	comRigidBody->createFixture(fixtureDef);
}

void CCComNormalObjet::onExit()
{
	CCLOG("CCComNormalObjet::onExit()");
}

void CCComNormalObjet::update(float delta)
{
	CCLOG("CCComNormalObjet::update()");
}
