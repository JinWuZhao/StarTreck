#ifndef __SCRIPTBASE_H__
#define __SCRIPTBASE_H__

#include "cocos2d.h"

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

protected:
	cocos2d::CCNode*			m_pNode;
};

#endif