#ifndef __PLANET_H__
#define __PLANET_H__

#include "Actor.h"

class Planet :
	public Actor
{
public:
	Planet(void);
	virtual ~Planet(void);

	virtual bool init();
	virtual void update(float dt);
	virtual void end();

};

#endif