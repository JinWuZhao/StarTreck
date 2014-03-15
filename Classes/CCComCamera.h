//摄像机组件，依赖组件：CCComRigidBody

#ifndef __CCCOMCAMERA_H__
#define __CCCOMCAMERA_H__

#include "cocos2d.h"

class Camera;
class CCComCamera :
	public cocos2d::CCComponent
{
private:
	CCComCamera();
public:
	virtual ~CCComCamera();

	static CCComCamera* create(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	void setBoundingBox(cocos2d::CCSize& boxSize);

private:
	void beginContact(cocos2d::CCNode* pOther);
	void endContact(cocos2d::CCNode* pOther);

	Camera*			m_pCamera;
};

#endif