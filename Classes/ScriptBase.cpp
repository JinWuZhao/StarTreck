#include "ScriptBase.h"


ScriptBase::ScriptBase(void)
	: CCObject(),
	m_pOwner(NULL)
{
}


ScriptBase::~ScriptBase(void)
{
}

bool ScriptBase::init()
{
	CCLOG("ScriptBase::init()");
	return true;
}

void ScriptBase::update(float dt)
{
	CCLOG("ScriptBase::update()");
}

void ScriptBase::end()
{
	CCLOG("ScriptBase::end()");
}

void ScriptBase::setNdoe( cocos2d::CCNode* pNode )
{
	if (!m_pOwner)
	{
		m_pOwner = pNode;
	}
}

void ScriptBase::destroySelf(void)
{
	if (m_pOwner)
	{
		m_pOwner->removeFromParent();
		m_pOwner = NULL;
	}
}
