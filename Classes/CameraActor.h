#ifndef __CAMERAACTOR_H__
#define __CAMERAACTOR_H__

#include "Actor.h"

class CameraActor :
	public Actor
{
public:
	CameraActor();
	virtual ~CameraActor();

	virtual bool init();
	virtual void update(float dt);
	virtual void end();

private:
	cocos2d::CCNode*	m_pTarget;
};

#endif