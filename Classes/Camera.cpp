#include "Camera.h"
#include "VisibleRect.h"
#include "CCComRigidBody.h"
#include "PhysicsWorld.h"

USING_NS_CC;

#define ACTIONTAG_CAMERAMOVING 90000

static Camera* _sharedCamera = NULL;

Camera::Camera()
:CCObject(),
m_bIsFollowOpen(true),
m_pRootNode(NULL),
m_pCenterNode(NULL),
m_nMoveSpeed(10.0f)
{
}


Camera::~Camera()
{
}

Camera* Camera::sharedCamera()
{
	if (!_sharedCamera)
	{
		_sharedCamera = new Camera();
	}
	return _sharedCamera;
}

void Camera::setRootNode(cocos2d::CCNode* root)
{
	CC_ASSERT(root && !m_pRootNode);
	m_pRootNode = root;
	if (m_pRootNode)
	{
		m_pRootNode->retain();
		m_pRootNode->setPosition(VisibleRect::center());
	}
}

void Camera::setFollowObjet(cocos2d::CCNode* center)
{
	CC_ASSERT(center && center->getParent() == m_pRootNode && !m_pCenterNode);
	m_pCenterNode = center;
	m_pCenterNode->retain();
	setPosition(m_pCenterNode->getPosition());
}

void Camera::setPosition(float x, float y)
{
	CC_ASSERT(m_pRootNode);
	if (m_pRootNode)
	{
		m_pRootNode->setPosition(VisibleRect::center() - ccp(x, y));
	}
}

void Camera::moveTo(float x, float y, bool smoothly /*= true*/)
{
	CC_ASSERT(m_pRootNode);
	if (m_pRootNode && !IsMoving())
	{
		float duration = m_pRootNode->getPosition().getDistance(ccp(x,y)) / m_nMoveSpeed;
		if (smoothly)
		{
			ccBezierConfig bezierCfg;
			bezierCfg.controlPoint_1 = ccp(2.f,1.f);
			bezierCfg.controlPoint_2 = ccp(4.f,0.f);
			bezierCfg.endPosition = VisibleRect::center() - ccp(x, y);
			CCBezierTo* bezierToAction = CCBezierTo::create(duration, bezierCfg);
			bezierToAction->setTag(ACTIONTAG_CAMERAMOVING);
			m_pRootNode->runAction(bezierToAction);
		}
		else
		{
			CCMoveTo* moveToAction = CCMoveTo::create(duration, VisibleRect::center() - ccp(x, y));
			moveToAction->setTag(ACTIONTAG_CAMERAMOVING);
			m_pRootNode->runAction(moveToAction);
		}
	}
}

void Camera::setBoundingBox(const cocos2d::CCSize& boxSize)
{
	CC_ASSERT(boxSize.height > 0 && boxSize.width > 0);
	m_BoundingBox.origin = ccp(-boxSize.width/2, -boxSize.height/2);
	m_BoundingBox.size = boxSize;
}

void Camera::update(float delta)
{
	if (!m_pCenterNode || !m_bIsFollowOpen)
	{
		return ;
	}

	CC_ASSERT(m_pRootNode);
	if (m_pRootNode)
	{
		CCPoint centerPos = m_pCenterNode->getPosition();
		CC_ASSERT(m_BoundingBox.size.height > 0 && m_BoundingBox.size.width > 0);
		m_BoundingBox.origin = getPosition()-ccp(m_BoundingBox.size.width/2,m_BoundingBox.size.height/2);

		CCComRigidBody* comRigidBody = static_cast<CCComRigidBody*>(m_pCenterNode->getComponent("CCComRigidBody"));
		CC_ASSERT(comRigidBody);
		CCPoint velocity = comRigidBody->getVelocity();

		if (!m_BoundingBox.containsPoint(centerPos))
		{
			if (IsMoving())
			{
				m_pRootNode->stopActionByTag(ACTIONTAG_CAMERAMOVING);
			}
			CCPoint displacement = velocity*delta;
			setPosition(getPosition() + displacement);
		}
		else if (velocity.equals(CCPointZero) && centerPos.fuzzyEquals(centerPos,1.0f))
		{
			if (!IsMoving())
			{
				moveTo(centerPos, true);
			}
		}
	}

// 	CCLOG("Pos.x:%f, Pos.y:%f.", getPosition().x, getPosition().y);
// 	if (!m_BoundingBox.containsPoint(m_pCenterNode->getPosition()))
// 	{
// 		CCLOG("Out of range!");
// 	}
}

void Camera::reset(void)
{
	m_bIsFollowOpen = true;
	m_nMoveSpeed = 10.f;
	m_pRootNode->stopActionByTag(ACTIONTAG_CAMERAMOVING);
	setPosition(CCPointZero);
	CC_SAFE_RELEASE_NULL(m_pCenterNode);
	CC_SAFE_RELEASE_NULL(m_pRootNode);
	m_BoundingBox = CCRectZero;

}

bool Camera::IsMoving(void)
{
	CC_ASSERT(m_pRootNode);
	if (m_pRootNode)
	{
		return (m_pRootNode->numberOfRunningActions() > 0);
	}
	return false;
}

cocos2d::CCPoint Camera::getPosition(void)
{
	CC_ASSERT(m_pRootNode);
	if (m_pRootNode)
	{
		return VisibleRect::center() - m_pRootNode->getPosition();
	}
	return CCPointZero;
}
