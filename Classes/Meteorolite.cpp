#include "Meteorolite.h"
#include "GlobalDefine.h"
#include "CCComCelestialBody.h"
#include "CCComRigidBody.h"
#include "IContactListener.h"

USING_NS_CC;

Meteorolite::Meteorolite( void )
	: Actor()
{

}

Meteorolite::~Meteorolite( void )
{

}

bool Meteorolite::init()
{
	bool bRet = false;
	do 
	{
		CCLOG("Meteorolite::init() begin.");
		CC_BREAK_IF(!Actor::init());

		CCComCelestialBody* comCelestialBody = CCComCelestialBody::create();
		CC_BREAK_IF(!comCelestialBody);
		comCelestialBody->setType(CCComCelestialBody::E_METEOROLITE);
		if (!m_pOwner->addComponent(comCelestialBody))
		{
			CC_SAFE_DELETE(comCelestialBody);
			return false;
		}

		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_BREAK_IF(!comRigidBody);
		comRigidBody->registerBeginContactEvent(this, contact_selector(Meteorolite::beginContact));

		bRet = true;
		CCLOG("Meteorolite::init() success!");
	} while (0);
	return bRet;
}

void Meteorolite::update( float dt )
{
}

void Meteorolite::end()
{

}

void Meteorolite::beginContact(cocos2d::CCNode* pOther)
{
	if (pOther)
	{
		if (pOther->getTag()/ID_MASK != ID_METEOROLITE)
		{
			destroySelf();
		}
	}
}
