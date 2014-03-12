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

	//���ó������ڵ�
	void setRootNode(cocos2d::CCNode* root);

	//���ø������
	void setFollowObjet(cocos2d::CCNode* center);

	//�����ӿ�λ��
	void setPosition(float x, float y);
	void setPosition(const cocos2d::CCPoint& pos)
	{
		setPosition(pos.x, pos.y);
	}

	//�ƶ��ӿڵ�ĳλ��
	void moveTo(float x, float y, bool smoothly = false);
	void moveTo(const cocos2d::CCPoint& pos, bool smoothly = false)
	{
		moveTo(pos.x, pos.y, smoothly);
	}

	//�趨�ڲ���ײ��ߴ�,��ײ�����ĵ�λ���ӿ����ĵ�
	void setBoundingBox(const cocos2d::CCSize& boxSize);

	void update(float delta);

	//�������
	void reset(void);

	//�Ƿ����Զ�����
	CC_SYNTHESIZE(bool, m_bIsFollowOpen, IsFollowOpen);

	//�ӿ��ƶ��ٶ�
	CC_SYNTHESIZE(float, m_nMoveSpeed, MoveSpeed);

	//�ӿ��Ƿ����ƶ���
	bool IsMoving(void);

	cocos2d::CCPoint getPosition(void);

private:
	
	cocos2d::CCNode*			m_pRootNode;
	cocos2d::CCNode*			m_pCenterNode;

	cocos2d::CCRect				m_BoundingBox;
};

#endif