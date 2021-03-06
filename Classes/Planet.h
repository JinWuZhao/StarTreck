//����
#ifndef __PLANET_H__
#define __PLANET_H__

#include "StarBase.h"

class Planet :
	public StarBase
{
public:
	Planet();
	virtual ~Planet();

	virtual bool init();

	virtual void update(float dt);

	virtual void end();

private:
	void beginContact(cocos2d::CCNode* pOther);
};

#endif