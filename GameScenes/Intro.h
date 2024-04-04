#ifndef __INTRO_H__
#define __INTRO_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <iostream>
using namespace std;

USING_NS_CC;

#define TAG_START		0
#define TAG_ITEM		1
#define TAG_EXIT		2

class Intro : public cocos2d::Layer
{
protected:

	Size mVisibleSize = Director::getInstance()->getVisibleSize(); //화면 해상도
	Vec2 mOrigin = Director::getInstance()->getVisibleOrigin(); //정가운데

public:

	bool isTouch;

	static Scene* createScene();
	virtual bool init();
	void ChangeScnene();
	virtual void onInit(); //초기화
	virtual void onRelease(); //메모리삭제
	virtual void onLoad(); //불러오는 데이터 로드
	virtual bool onTouch(Touch *touch, Event * event);

	CREATE_FUNC(Intro);
};

#endif // __HELLOWORLD_SCENE_H__
