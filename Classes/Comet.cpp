#include "Comet.h"
#include "CCComCelestialBody.h"
#include "CCComGravity.h"


Comet::Comet()
:Actor()
{
}


Comet::~Comet()
{
}

bool Comet::init()
{
	bool bRet = false;
	do
	{
		CCLOG("Comet::init() begin.");
		CC_BREAK_IF(!Actor::init());

		CCComCelestialBody* comCelestialBody = CCComCelestialBody::create();
		CC_BREAK_IF(!comCelestialBody);
		comCelestialBody->setType(CCComCelestialBody::E_COMET);
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
		CCLOG("Comet::init() success!");
	} while (0);
	return bRet;
}

void Comet::update(float dt)
{

}

void Comet::end()
{

}
