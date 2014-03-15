#include "FixedStar.h"
#include "CCComRigidBody.h"
#include "GlobalDefine.h"
#include "IContactListener.h"

FixedStar::FixedStar()
:StarBase()
{
}


FixedStar::~FixedStar()
{
}

bool FixedStar::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!StarBase::init());
		
		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_BREAK_IF(!comRigidBody);
		comRigidBody->registerBeginContactEvent(this, contact_selector(FixedStar::beginContact));

		bRet = true;
	} while (0);
	return bRet;
}

void FixedStar::update(float dt)
{
	
}

void FixedStar::end()
{
	
}

void FixedStar::beginContact(cocos2d::CCNode* pOther)
{
	if (pOther)
	{
		if (pOther->getTag() / ID_MASK == ID_COMET)
		{
			//TODO
		}
	}
}
