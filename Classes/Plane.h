#ifndef __PLANE_H__
#define __PLANE_H__

#include "Actor.h"

class Plane :
	public Actor
{
public:
	Plane(void);
	virtual ~Plane(void);

	virtual bool init();
	virtual void update(float dt);
	virtual void end();
};

#endif