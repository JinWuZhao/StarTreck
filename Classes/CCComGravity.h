//万有引力组件

#ifndef __CCCOMGRAVITY_H__
#define __CCCOMGRAVITY_H__

#include "cocos2d.h"
#include <list>

class CCComGravity :
	public cocos2d::CCComponent
{
private:
	CCComGravity();
public:
	virtual ~CCComGravity();

	static CCComGravity* create(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	float computeMass(void);
	float computeRadius(void);

	virtual void setDensity(float density);

	CC_SYNTHESIZE_READONLY(float, m_nRadius, Radius);
	CC_SYNTHESIZE_READONLY(float, m_nDensity, Density);
	CC_SYNTHESIZE_READONLY(float, m_nMass, Mass);

private:
	//std::list<b2Body*>		m_AttractedBodies; //受引力影响的body
};

#endif

