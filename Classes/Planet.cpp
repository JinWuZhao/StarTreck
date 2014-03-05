#include "Planet.h"

#include "cocos-ext.h"
#include "PhysicsWorld.h"
#include "CCComRigidBody.h"
#include "CCComGravity.h"
#include "CCComPlanet.h"

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

		CCComPlanet* comPlanet = CCComPlanet::create();
		CC_BREAK_IF(!comPlanet);
		if (!m_pNode->addComponent(comPlanet))
		{
			CC_SAFE_DELETE(comPlanet);
			return false;
		}

		CCComGravity* comGravity = CCComGravity::create();
		CC_BREAK_IF(!comGravity);
		if (!m_pNode->addComponent(comGravity))
		{
			CC_SAFE_DELETE(comGravity);
			return false;
		}

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
