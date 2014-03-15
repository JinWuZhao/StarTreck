#ifndef __STARBASE_H__
#define __STARBASE_H__

#include "Actor.h"

class StarBase :
	public Actor
{
public:
	StarBase(void);
	virtual ~StarBase(void);

	virtual bool init();
	virtual void update(float dt);
	virtual void end();
};

#endif