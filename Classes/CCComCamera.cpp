#include "CCComCamera.h"
#include "Camera.h"
#include "NodeInit.h"
#include "CCComRigidBody.h"
#include "PhysicsWorld.h"
#include "VisibleRect.h"
#include "IContactListener.h"

USING_NS_CC;

#define ACTIVEZONE_RADIUS ((VisibleRect::rightTop()-VisibleRect::leftBottom()).getLength()/4*3)

CCComCamera::CCComCamera()
:CCComponent(),
m_pCamera(NULL)
{
}


CCComCamera::~CCComCamera()
{
}

CCComCamera* CCComCamera::create(void)
{
	CCComCamera * pRet = new CCComCamera();
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

bool CCComCamera::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComCamera");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComCamera::onEnter()
{
	CCLOG("CCComCamera::onEnter()");
	m_pCamera = Camera::sharedCamera();
	m_pCamera->setRootNode(NodeInitiator::sharedNodeInitiator()->getRootNode());
	m_pCamera->setFollowObjet(m_pOwner);
	m_pCamera->setBoundingBox(CCSizeMake(200, 200));

	//create activezone sensor
	//get comRigidbody
	CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
	CC_ASSERT(comRigidBody);

	//create body
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	float ratio = PhysicsWorld::sharedPhysicsWorld()->getP2mRatio();
	CCPoint pos = m_pOwner->getPosition();
	bodyDef.position = b2Vec2(ratio*pos.x, ratio*pos.y);
	b2Body* body = comRigidBody->createBody(bodyDef);

	//create fixture
	b2CircleShape shape;
	shape.m_radius =  ACTIVEZONE_RADIUS * ratio * m_pOwner->getScale();
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.isSensor = true;
	comRigidBody->createFixture(fixtureDef);

	//register event
	PhysicsWorld::sharedPhysicsWorld()->registerBeginContactEvent(body, this, contact_selector(CCComCamera::beginContact));
	PhysicsWorld::sharedPhysicsWorld()->registerEndContactEvent(body, this, contact_selector(CCComCamera::endContact));
}

void CCComCamera::onExit()
{
	CCLOG("CCComCamera::onExit()");
	Camera::sharedCamera()->reset();
}

void CCComCamera::update(float delta)
{
	//CCLOG("CCComCamera::update()");
	Camera::sharedCamera()->update(delta);
}

void CCComCamera::setBoundingBox(cocos2d::CCSize& boxSize)
{
	m_pCamera->setBoundingBox(boxSize);
}

void CCComCamera::beginContact(cocos2d::CCNode* pOther)
{
	//激活区域内的对象
	if (pOther)
	{
		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(pOther->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		comRigidBody->setVisible(true);
	}
}

void CCComCamera::endContact(cocos2d::CCNode* pOther)
{
	//失活区域外的对象
	if (pOther)
	{
		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(pOther->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		comRigidBody->setVisible(false);
	}
}
