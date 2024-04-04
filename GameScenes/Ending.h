#ifndef __ENDING_H__
#define __ENDING_H__

#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;

#define TAG_SCORE 300

class Ending : public Layer
{
private:
	Character* mCharacter;
	Size mVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 mOrigin = Director::getInstance()->getVisibleOrigin();

public:
	bool init();
	static Scene* CreateScene();
	void onGameScene();
	void onMainScene();
	void DrawEnd();

	void GameReplay(Ref *Sender);
	void GameGoHome(Ref *Sender);

	CREATE_FUNC(Ending);
};
#endif