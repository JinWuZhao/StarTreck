//脚本组件，为CCNode添加执行逻辑

#ifndef __CCCOMSCRIPT_H__
#define __CCCOMSCRIPT_H__

#include "cocos2d.h"
#include <string>

class ScriptBase;

class CCComScript :
	public cocos2d::CCComponent
{
private:
	CCComScript(void);
public:
	virtual ~CCComScript(void);

	static CCComScript* create(void);

	virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float delta);

	void setScript(ScriptBase* pScript);
	ScriptBase* getScript(void) { return m_pScript; }

	std::string getScriptName(void);

private:
	ScriptBase*		m_pScript;
};

#endif