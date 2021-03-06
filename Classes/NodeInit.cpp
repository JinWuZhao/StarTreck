#include "NodeInit.h"
#include "ScriptBase.h"
#include "CCComScript.h"
#include "ScriptDefine.h"

USING_NS_CC;

static NodeInitiator* _sharedNodeInitiator = NULL;
NodeInitiator::NodeInitiator(void)
	: CCObject(),
	m_pRootNode(NULL)
{
}


NodeInitiator::~NodeInitiator(void)
{
}

NodeInitiator* NodeInitiator::sharedNodeInitiator()
{
	if (!_sharedNodeInitiator)
	{
		_sharedNodeInitiator = new NodeInitiator();
	}
	return _sharedNodeInitiator;
}

bool NodeInitiator::initNodeWithScript( cocos2d::CCNode* pNode, ScriptBase* pScript )
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!pNode);
		CC_BREAK_IF(!pScript);
		CCComScript* pComScript = CCComScript::create();
		CC_BREAK_IF(!pComScript);
		if (!pNode->addComponent(pComScript))
		{
			CC_SAFE_DELETE(pComScript);
			break;
		}
		pComScript->setScript(pScript);
		bRet = true;
	} while (0);
	return bRet;
}

bool NodeInitiator::initAllNodes( cocos2d::CCNode* pRoot )
{
	m_pRootNode = pRoot;
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!traverseChildren(pRoot));
		bRet = true;
	} while (0);

	if (!bRet)
	{
		CCLOG("Failed to init nodes.");
	}

	return bRet;
}

bool NodeInitiator::traverseChildren( cocos2d::CCNode* pRoot )
{
	bool bRet = false;
	do 
	{
		CCLOG("StartTraverseChild: %d", pRoot->getTag());
		CCObject* pNode = NULL;
		CCARRAY_FOREACH(pRoot->getChildren(), pNode)
		{
			ScriptBase* pScript = _createScript(static_cast<CCNode*>(pNode)->getTag());
			if (!pScript)
			{
				continue;
			}
			pScript->setRootNode(m_pRootNode);
			if (!initNodeWithScript(static_cast<CCNode*>(pNode), pScript))
			{
				CC_SAFE_DELETE(pScript);
				return false;
			}
			if (!traverseChildren(static_cast<CCNode*>(pNode)))
			{
				CCLOG("Failed to init node:%d.", ((CCNode*)pNode)->getTag());
				continue;
			}
		}
		CCLOG("FinishTraverseChild: %d", pRoot->getTag());
		bRet = true;
	} while (0);
	return bRet;
}