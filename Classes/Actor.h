#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "ScriptBase.h"

class CCComRigidBody;

class Actor :
	public ScriptBase
{
public:
	Actor(void);
	virtual ~Actor(void);

	virtual bool init();
	virtual void update(float dt);
	virtual void end();

protected:
	CCComRigidBody*			m_pRigidBody;
};

#endif