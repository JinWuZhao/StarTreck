#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::CCScene
{
public:

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float dt);

    // implement the "static node()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_H__
