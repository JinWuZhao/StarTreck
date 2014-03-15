#ifndef __PHYSICSWORLD_H__
#define __PHYSICSWORLD_H__

#include "cocos2d.h"
#include "Box2D.h"
#include <list>
#include "IContactListener.h"
#include <map>


class ContactEvent
{
public:
	b2Body* owner;
	cocos2d::CCObject* user;
	SEL_CONTACT beginContact;
	SEL_CONTACT endContact;

	ContactEvent(void)
		:owner(NULL),
		user(NULL),
		beginContact(NULL),
		endContact(NULL)
	{}
};

class PhysicsWorld : 
	public cocos2d::CCObject, public b2ContactListener
{
private:
	PhysicsWorld(void);

public:
	virtual ~PhysicsWorld(void);

	static PhysicsWorld* sharedPhysicsWorld();

	bool init();

	void update(float dt);

	void end();

	//����dynamic�б�
	void addToDynamicList(b2Body* pBody);
	//��ȡdynamic�б�
	void getDynamicList(std::list<b2Body*>& bodyList);
	//�ӱ���dynamic�б���ɾ��
	void removeFromDynamicList(b2Body* pBody);

	//��ѯ����body����
	int getBackupBodyCount();

	//��ȡһ���µ�body
	b2Body* getNewBody(const b2BodyDef& def);

	//����һ�����õ�body
	void collectBody(b2Body* pOldBody);

	//contact listener
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) {}
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

	//ע��contact�¼�
	void registerBeginContactEvent(b2Body* owner, cocos2d::CCObject* user, SEL_CONTACT sel);
	void registerEndContactEvent(b2Body* owner, cocos2d::CCObject* user, SEL_CONTACT sel);


	CC_SYNTHESIZE_READONLY(b2World*, m_pB2World, B2World);

	CC_SYNTHESIZE_READONLY(float, m_nPTM_RATIO, P2mRatio); // m/pixel

	CC_SYNTHESIZE_READONLY(float, m_nMTP_RATIO, M2pRatio); // pixel/m

	CC_SYNTHESIZE_READONLY(bool, m_bIsActive, IsActive);

	CC_SYNTHESIZE_READONLY(float, m_nGConst, GConst);

	CC_SYNTHESIZE_READONLY(int, m_nMaxBodyNum, MaxBodyNum);

private:

	void getEventsByKey(b2Body* key, std::list<ContactEvent>& eventList);

	std::list<b2Body*>			m_DynamicBodyList;

	std::list<b2Body*>			m_BackupBodyList;

	std::multimap<b2Body*, ContactEvent>		m_ContactEventMap;

};

#endif