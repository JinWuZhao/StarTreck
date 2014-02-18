#ifndef __CCCOMSCRIPT_H__
#define __CCCOMSCRIPT_H__

#include "cocos2d.h"

class ScriptBase;

class CCComScript :
	public cocos2d::CCComponent
{
private:
	CCComScript(void);
public:
	virtual ~CCComScript(void);

	virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);

	void setScript(ScriptBase* pScript);

	static CCComScript* create(void);

private:
	ScriptBase*		m_pScript;
};

#endif