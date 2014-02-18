#include "Planet.h"

#include "cocos-ext.h"
#include "PhysicsWorld.h"
#include "CCComRigidBody.h"

USING_NS_CC;
USING_NS_CC_EXT;

Planet::Planet( void )
	: Actor()
{

}

Planet::~Planet( void )
{

}

bool Planet::init()
{
	bool bRet = false;
	do 
	{
		CCLOG("Planet::init() begin.");
		CC_BREAK_IF(!Actor::init());

		//get bounding box
		CCComRender* comRender = static_cast<CCComRender*>(m_pNode->getComponent("CCArmature"));
		CCArmature* pArmature = static_cast<CCArmature*>(comRender->getNode());
		CCRect	bbox = pArmature->boundingBox();
		//create body
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		float ratio = PhysicsWorld::sharedPhysicsWorld()->getRatio();
		CCPoint pos = m_pNode->getPosition();
		bodyDef.position = b2Vec2( ratio*pos.x, ratio*pos.y);
		CC_BREAK_IF(m_pRigidBody->createBody(bodyDef));
		//create fixture
		b2CircleShape	shape;
		shape.m_radius = bbox.size.width/2*ratio*m_pNode->getScale();
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 10;
		fixtureDef.friction = 1;
		fixtureDef.restitution = 0;
		CC_BREAK_IF(m_pRigidBody->createFixture(fixtureDef));

		bRet = true;
		CCLOG("Planet::init() success!");
	} while (0);
	return bRet;
}

void Planet::update( float dt )
{

}

void Planet::end()
{

}
