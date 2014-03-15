//∫„–«
#ifndef __FIXEDSTAR_H__
#define __FIXEDSTAR_H__

#include "StarBase.h"

class FixedStar :
	public StarBase
{
public:
	FixedStar();
	virtual ~FixedStar();

	virtual bool init();

	virtual void update(float dt);

	virtual void end();

private:
	void beginContact(cocos2d::CCNode* pOther);

};

#endif