//ºÚ¶´
#ifndef __BLACKHOLE_H__
#define __BLACKHOLE_H__

#include "StarBase.h"

class BlackHole :
	public StarBase
{
public:
	BlackHole();
	virtual ~BlackHole();

	virtual bool init();

	virtual void update(float dt);

	virtual void end();

private:
	void beginContact(cocos2d::CCNode* pOther);
};

#endif