#ifndef __METEOROLITE_H__
#define __METEOROLITE_H__

#include "Actor.h"

class Meteorolite :
	public Actor
{
public:
	Meteorolite(void);
	virtual ~Meteorolite(void);

	virtual bool init();
	virtual void update(float dt);
	virtual void end();

private:
	//contact listener
	void beginContact(cocos2d::CCNode* pOther);
};

#endif