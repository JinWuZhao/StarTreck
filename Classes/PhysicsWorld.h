#ifndef __PHYSICSWORLD_H__
#define __PHYSICSWORLD_H__

#include "cocos2d.h"
#include "Box2D.h"

class PhysicsWorld : 
	public cocos2d::CCObject
{
private:
	PhysicsWorld(void);

public:
	virtual ~PhysicsWorld(void);

	static PhysicsWorld* sharedPhysicsWorld();

	bool init();

	void update(float dt);

	void end();

	CC_SYNTHESIZE_READONLY(b2World*, m_pB2World, B2World);

	CC_SYNTHESIZE_READONLY(int, m_nPTM_RATIO, Ratio);

	CC_SYNTHESIZE_READONLY(bool, m_bIsActive, IsActive);
};

#endif