#ifndef __ICONTACTLISTENER_H__
#define __ICONTACTLISTENER_H__

namespace cocos2d
{
	class CCNode;
	class CCObject;
};

//BeginContact
//void BeginContact(cocos2d::CCNode* pNode) = 0;

//EndContact
//void EndContact(cocos2d::CCNode* pNode) = 0;

typedef void (cocos2d::CCObject::*SEL_CONTACT)(cocos2d::CCNode*);

#define contact_selector(_SELECTOR) (SEL_CONTACT)(&_SELECTOR)

#endif