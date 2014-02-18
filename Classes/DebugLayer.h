#ifndef __DEBUGLAYER_H__
#define __DEBUGLAYER_H__

#include "cocos2d.h"

class GLESDebugDraw;

class DebugLayer : public cocos2d::CCLayer
{
public:

	virtual bool init(); 

	virtual void onEnter();

	virtual void onExit();

	virtual void draw();

    // implement the "static node()" method manually
    CREATE_FUNC(DebugLayer);

private:
	GLESDebugDraw*		m_pDebugDraw;
};

#endif
