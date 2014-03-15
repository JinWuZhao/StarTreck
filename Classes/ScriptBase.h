#ifndef __SCRIPTBASE_H__
#define __SCRIPTBASE_H__

#include "cocos2d.h"
#include <string>

class ScriptBase :
	public cocos2d::CCObject
{
public:
	ScriptBase(void);
	virtual ~ScriptBase(void);

	virtual bool init();
	virtual void update(float dt);
	virtual void end();

	void setNdoe(cocos2d::CCNode* pNode);

	void destroySelf(void);

	CC_SYNTHESIZE(std::string, m_strName, Name);
	CC_SYNTHESIZE(cocos2d::CCNode*, m_pRootNode, RootNode);

protected:
	cocos2d::CCNode*			m_pOwner;
};

#endif