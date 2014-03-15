#include "CameraActor.h"
#include "CCComCamera.h"
#include "cocos-ext.h"
#include "CCComRigidBody.h"
#include "GlobalDefine.h"

USING_NS_CC;
USING_NS_CC_EXT;

CameraActor::CameraActor()
:Actor(),
m_pTarget(NULL)
{
}


CameraActor::~CameraActor()
{
}

bool CameraActor::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!Actor::init());

		CCComCamera* comCamera = CCComCamera::create();
		CC_BREAK_IF(!comCamera);
		if (!m_pOwner->addComponent(comCamera))
		{
			CC_SAFE_DELETE(comCamera);
			return false;
		}
		CCComRender* comRender = static_cast<CCComRender*>(m_pOwner->getComponent("CCComRender"));
		if (comRender && comRender->getNode())
		{
			comRender->getNode()->setVisible(false);
		}
		m_pTarget = m_pRootNode->getChildByTag(TAG_PLAYERNODE);
		CC_BREAK_IF(m_pTarget);
		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		comRigidBody->setPosition(m_pTarget->getPosition());
		m_pOwner->setZOrder(ZORDER_CAMERALAYER);
		bRet = true;
	} while (0);
	return bRet;
}

void CameraActor::update(float dt)
{
	if (m_pTarget)
	{
		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pOwner->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		comRigidBody->setPosition(m_pTarget->getPosition());
	}
}

void CameraActor::end()
{
	
}
