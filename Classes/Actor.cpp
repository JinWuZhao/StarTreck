#include "Actor.h"
#include "CCComRigidBody.h"

USING_NS_CC;

Actor::Actor(void)
	: ScriptBase(),
	m_pRigidBody(NULL)
{
}

Actor::~Actor(void)
{

}

bool Actor::init()
{
	bool bRet = false;
	do 
	{
		//CCLOG("Actor::init() begin.");
		m_pRigidBody = CCComRigidBody::create();
		CC_BREAK_IF(!m_pRigidBody);
		if (!m_pNode->addComponent(m_pRigidBody))
		{
			CC_SAFE_DELETE(m_pRigidBody);
			break;
		}
		bRet = true;
		//CCLOG("Actor::init() success!");
	} while (0);
	return bRet;
}

void Actor::update( float dt )
{

}

void Actor::end()
{

}
