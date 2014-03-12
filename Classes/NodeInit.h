#ifndef __NODEINIT_H__
#define __NODEINIT_H__

#include "cocos2d.h"

class ScriptBase;

class NodeInitiator :
	public cocos2d::CCObject
{
private:
	NodeInitiator(void);
public:
	virtual ~NodeInitiator(void);

	static NodeInitiator* sharedNodeInitiator();

	bool initAllNodes(cocos2d::CCNode* pRoot);

	bool initNodeWithScript(cocos2d::CCNode* pNode, ScriptBase* pScript);

	cocos2d::CCNode* getRootNode() { return m_pRootNode; }

private:
	//recursion
	bool traverseChildren(cocos2d::CCNode* pRoot);

	cocos2d::CCNode*	m_pRootNode; //CocoStudioÖÐµÄRootNode
};

#endif