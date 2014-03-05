//宇宙中一般的小型受力物体
#ifndef __CCCOMNORMALOBJECT_H__
#define __CCCOMNORMALOBJECT_H__

#include "cocos2d.h"

class CCComNormalObjet :
	public cocos2d::CCComponent
{
private:
	CCComNormalObjet();
public:
	virtual ~CCComNormalObjet();

	static CCComNormalObjet* create(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);
};

#endif