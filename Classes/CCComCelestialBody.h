//天体组件，依赖组件：CCComRigidBody、CCComGravity

#ifndef __CCCOMCELESTIALBODY_H__
#define __CCCOMCELESTIALBODY_H__

#include "cocos2d.h"

class CCComCelestialBody :
	public cocos2d::CCComponent
{
private:
	CCComCelestialBody();
public:
	virtual ~CCComCelestialBody();

	static CCComCelestialBody* create(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	enum E_BODYTYPE
	{
		E_PLANET = 0,
		E_METEOROLITE,
		E_COMET
	};

	CC_SYNTHESIZE(cocos2d::CCNode*, m_pCenterPlanet, CenterPlanet);
	CC_SYNTHESIZE(E_BODYTYPE, m_eType, Type);
};

#endif