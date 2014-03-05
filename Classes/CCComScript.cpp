#include "CCComScript.h"
#include "ScriptBase.h"

USING_NS_CC;

CCComScript::CCComScript(void)
	: CCComponent(),
	m_pScript(NULL)
{
}

CCComScript::~CCComScript(void)
{
}

bool CCComScript::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCComponent::init());
		setName("CCComScript");
		bRet = true;
	} while (0);
	return bRet;
}

void CCComScript::onEnter()
{

}

void CCComScript::onExit()
{
	if (m_pScript)
	{
		m_pScript->end();
		CC_SAFE_DELETE(m_pScript);
	}
}

void CCComScript::update( float delta )
{
	if (m_pScript)
	{
		m_pScript->update(delta);
	}
}

void CCComScript::setScript( ScriptBase* pScript )
{
	CC_SAFE_DELETE(m_pScript);
	m_pScript = pScript;
	if (m_pScript)
	{
		m_pScript->setNdoe(getOwner());
		m_pScript->init();
	}
}

CCComScript* CCComScript::create( void )
{
	CCComScript * pRet = new CCComScript();
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

std::string CCComScript::getScriptName(void)
{
	return m_pScript->getName();
}
