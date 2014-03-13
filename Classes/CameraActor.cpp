#include "CameraActor.h"
#include "CCComCamera.h"
#include "cocos-ext.h"

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
		if (!m_pNode->addComponent(comCamera))
		{
			CC_SAFE_DELETE(comCamera);
			return false;
		}
		CCComRender* comRender = static_cast<CCComRender*>(m_pNode->getComponent("CCComRender"));
		if (comRender && comRender->getNode())
		{
			comRender->getNode()->setVisible(false);
		}
		m_pTarget = m_pRootNode->getChildByTag(10200);
		CC_BREAK_IF(m_pTarget);
		m_pTarget->retain();
		m_pNode->setPosition(m_pTarget->getPosition());
		m_pNode->setZOrder(999);
		bRet = true;
	} while (0);
	return bRet;
}

void CameraActor::update(float dt)
{
	if (m_pTarget)
	{
		m_pNode->setPosition(m_pTarget->getPosition());
	}
}

void CameraActor::end()
{
	CC_SAFE_RELEASE_NULL(m_pTarget);
}
