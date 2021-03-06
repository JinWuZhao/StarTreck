#include "Planet.h"
#include "IContactListener.h"
#include "CCComRigidBody.h"
#include "GlobalDefine.h"

Planet::Planet()
:StarBase()
{
}


Planet::~Planet()
{
}

bool Planet::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!StarBase::init());

		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_BREAK_IF(!comRigidBody);
		comRigidBody->registerBeginContactEvent(this, contact_selector(Planet::beginContact));

		bRet = true;
	} while (0);
	return bRet;
}

void Planet::update(float dt)
{
	
}

void Planet::end()
{
	
}

void Planet::beginContact(cocos2d::CCNode* pOther)
{
	if (pOther)
	{
		if (pOther->getTag()/ID_MASK == ID_COMET)
		{
			//TODO
		}
	}
}
