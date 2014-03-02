#include "Actor.h"
#include "CCComRigidBody.h"

USING_NS_CC;

Actor::Actor(void)
	: ScriptBase()
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
		CCComRigidBody* comRigidBody = CCComRigidBody::create();
		CC_BREAK_IF(!comRigidBody);
		if (!m_pNode->addComponent(comRigidBody))
		{
			CC_SAFE_DELETE(comRigidBody);
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
