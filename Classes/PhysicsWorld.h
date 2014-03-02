#ifndef __PHYSICSWORLD_H__
#define __PHYSICSWORLD_H__

#include "cocos2d.h"
#include "Box2D.h"
#include <list>

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

	//���뱸���б�
	void addToBackupList(b2Body* pBody);
	//��ȡ�����б�
	void getBackupList(std::list<b2Body*>& bodyList);
	//�ӱ����б���ɾ��
	void removeFromBackupList(b2Body* pBody);

	CC_SYNTHESIZE_READONLY(b2World*, m_pB2World, B2World);

	CC_SYNTHESIZE_READONLY(float, m_nPTM_RATIO, P2mRatio); // m/pixel

	CC_SYNTHESIZE_READONLY(float, m_nMTP_RATIO, M2pRatio); // pixel/m

	CC_SYNTHESIZE_READONLY(bool, m_bIsActive, IsActive);

	CC_SYNTHESIZE_READONLY(float, m_nGConst, GConst);

private:
	std::list<b2Body*>			m_BodyList;
};

#endif