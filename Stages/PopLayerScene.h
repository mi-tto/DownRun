#ifndef __POPLAYERSCENE_H__
#define __POPLAYERSCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PopLayer : public cocos2d::Layer
{
private:

	Size mVisibleSize;
	Vec2 mOrigin;

public:

	virtual bool init();
	static Scene* createScene();
	void GameContinue(Ref *Sender);
	void GameReplay(Ref *Sender);
	void GameGoHome(Ref *Sender);

	CREATE_FUNC(PopLayer);
};

#endif // _PopLayer__
