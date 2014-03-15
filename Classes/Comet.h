#ifndef __COMET_H__
#define __COMET_H__
#include "Actor.h"

class Comet :
	public Actor
{
public:
	Comet();
	virtual ~Comet();

	virtual bool init();
	virtual void update(float dt);
	virtual void end();
};

#endif