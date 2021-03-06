//刚体组件

#ifndef __CCCOMRIGIDBODY_H__
#define __CCCOMRIGIDBODY_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "IContactListener.h"

class CCComRigidBody :
	public cocos2d::CCComponent
{
private:
	CCComRigidBody(void);
public:
	virtual ~CCComRigidBody(void);

	static CCComRigidBody* create(void);

	virtual bool init();
	virtual void onEnter();
	virtual void onExit();
	virtual void update(float delta);

	b2Body* createBody(const b2BodyDef& bodyDef, bool bBackup = false);

	b2Fixture* createFixture(const b2FixtureDef& fixtureDef);

	void setVisible(bool visible);

	void applyForceToCenter(const b2Vec2& force);

	void applyForce(const b2Vec2& force, const b2Vec2& point);

	void applyTorque(float torque);

	cocos2d::CCPoint getVelocity(void);

	void setPosition(const cocos2d::CCPoint& pos);

	//为当前body注册contact事件
	void registerBeginContactEvent(cocos2d::CCObject* user, SEL_CONTACT sel);
	void registerEndContactEvent(cocos2d::CCObject* user, SEL_CONTACT sel);

	CC_SYNTHESIZE_READONLY(b2Body*, m_pBody, Body);
	CC_SYNTHESIZE_READONLY(bool, m_bIsDynamic, IsDynamic);
};

#endif