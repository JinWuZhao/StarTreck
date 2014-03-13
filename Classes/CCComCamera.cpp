#include "CCComCamera.h"
#include "Camera.h"
#include "NodeInit.h"

USING_NS_CC;

CCComCamera::CCComCamera()
:CCComponent(),
m_pCamera(NULL)
{
}


CCComCamera::~CCComCamera()
{
}

CCComCamera* CCComCamera::create(void)
{
	CCComCamera * pRet = new CCComCamera();
	if (pRet != NULL && pRet->init())
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CCComCamera::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComCamera");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComCamera::onEnter()
{
	CCLOG("CCComCamera::onEnter()");
	m_pCamera = Camera::sharedCamera();
	m_pCamera->setRootNode(NodeInitiator::sharedNodeInitiator()->getRootNode());
	m_pCamera->setFollowObjet(m_pOwner);
	m_pCamera->setBoundingBox(CCSizeMake(200, 200));
}

void CCComCamera::onExit()
{
	CCLOG("CCComCamera::onExit()");
	Camera::sharedCamera()->reset();
}

void CCComCamera::update(float delta)
{
	//CCLOG("CCComCamera::update()");
	Camera::sharedCamera()->update(delta);
}

void CCComCamera::setBoundingBox(cocos2d::CCSize& boxSize)
{
	m_pCamera->setBoundingBox(boxSize);
}
