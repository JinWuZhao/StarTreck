#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "cocos2d.h"

class Camera :
	public cocos2d::CCObject
{
private:
	Camera();
public:
	virtual ~Camera();

	static Camera* sharedCamera();

	//设置场景根节点
	void setRootNode(cocos2d::CCNode* root);

	//设置跟随对象
	void setFollowObjet(cocos2d::CCNode* center);

	//更改视口位置
	void setPosition(float x, float y);
	void setPosition(const cocos2d::CCPoint& pos)
	{
		setPosition(pos.x, pos.y);
	}

	//移动视口到某位置
	void moveTo(float x, float y, bool smoothly = false);
	void moveTo(const cocos2d::CCPoint& pos, bool smoothly = false)
	{
		moveTo(pos.x, pos.y, smoothly);
	}

	//设定内部碰撞框尺寸,碰撞框中心点位于视口中心点
	void setBoundingBox(const cocos2d::CCSize& boxSize);

	void update(float delta);

	//重置相机
	void reset(void);

	//是否开启自动跟随
	CC_SYNTHESIZE(bool, m_bIsFollowOpen, IsFollowOpen);

	//视口移动速度
	CC_SYNTHESIZE(float, m_nMoveSpeed, MoveSpeed);

	//视口是否在移动中
	bool IsMoving(void);

	cocos2d::CCPoint getPosition(void);

private:
	
	cocos2d::CCNode*			m_pRootNode;
	cocos2d::CCNode*			m_pCenterNode;

	cocos2d::CCRect				m_BoundingBox;
};

#endif