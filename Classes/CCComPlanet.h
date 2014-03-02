#ifndef __CCCOMPLANET_H__
#define __CCCOMPLANET_H__

#include "cocos2d.h"

class CCComPlanet :
	public cocos2d::CCComponent
{
private:
	CCComPlanet();
public:
	virtual ~CCComPlanet();

	static CCComPlanet* create(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	CC_SYNTHESIZE(cocos2d::CCNode*, m_pCenterPlanet, CenterPlanet);
};

#endif