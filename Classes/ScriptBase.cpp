#include "ScriptBase.h"


ScriptBase::ScriptBase(void)
	: CCObject(),
	m_pNode(NULL)
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
	if (!m_pNode)
	{
		m_pNode = pNode;
	}
}
