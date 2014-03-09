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

	//加入dynamic列表。
	void addToDynamicList(b2Body* pBody);
	//读取dynamic列表。
	void getDynamicList(std::list<b2Body*>& bodyList);
	//从备用dynamic列表中删除
	void removeFromDynamicList(b2Body* pBody);

	//查询备用body数量
	int getBackupBodyCount();

	//获取一个新的body
	b2Body* getNewBody(const b2BodyDef& def);

	//回收一个无用的body
	void collectBody(b2Body* pOldBody);

	CC_SYNTHESIZE_READONLY(b2World*, m_pB2World, B2World);

	CC_SYNTHESIZE_READONLY(float, m_nPTM_RATIO, P2mRatio); // m/pixel

	CC_SYNTHESIZE_READONLY(float, m_nMTP_RATIO, M2pRatio); // pixel/m

	CC_SYNTHESIZE_READONLY(bool, m_bIsActive, IsActive);

	CC_SYNTHESIZE_READONLY(float, m_nGConst, GConst);

	CC_SYNTHESIZE_READONLY(int, m_nMaxBodyNum, MaxBodyNum);

private:
	std::list<b2Body*>			m_DynamicBodyList;

	std::list<b2Body*>			m_BackupBodyList;

};

#endif