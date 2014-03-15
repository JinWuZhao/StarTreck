#include "BlackHole.h"
#include "CCComRigidBody.h"
#include "GlobalDefine.h"
#include "IContactListener.h"

BlackHole::BlackHole()
:StarBase()
{
}


BlackHole::~BlackHole()
{
}

bool BlackHole::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!StarBase::init());

		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_BREAK_IF(!comRigidBody);
		comRigidBody->registerBeginContactEvent(this, contact_selector(BlackHole::beginContact));

		bRet = true;
	} while (0);
	return bRet;
}

void BlackHole::update(float dt)
{
	
}

void BlackHole::end()
{
	
}

void BlackHole::beginContact(cocos2d::CCNode* pOther)
{
	if (pOther)
	{
		if (pOther->getTag() / ID_MASK == ID_COMET)
		{
			//TODO
		}
	}
}
