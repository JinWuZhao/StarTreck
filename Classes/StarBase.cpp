#include "StarBase.h"
#include "PhysicsWorld.h"
#include "CCComGravity.h"
#include "CCComCelestialBody.h"

USING_NS_CC;

StarBase::StarBase( void )
	: Actor()
{

}

StarBase::~StarBase( void )
{

}

bool StarBase::init()
{
	bool bRet = false;
	do 
	{
		CCLOG("Planet::init() begin.");
		CC_BREAK_IF(!Actor::init());

		CCComCelestialBody* comCelestialBody = CCComCelestialBody::create();
		CC_BREAK_IF(!comCelestialBody);
		comCelestialBody->setType(CCComCelestialBody::E_PLANET);
		if (!m_pOwner->addComponent(comCelestialBody))
		{
			CC_SAFE_DELETE(comCelestialBody);
			return false;
		}

		CCComGravity* comGravity = CCComGravity::create();
		CC_BREAK_IF(!comGravity);
		if (!m_pOwner->addComponent(comGravity))
		{
			CC_SAFE_DELETE(comGravity);
			return false;
		}

		bRet = true;
		CCLOG("Planet::init() success!");
	} while (0);
	return bRet;
}

void StarBase::update( float dt )
{

}

void StarBase::end()
{

}
