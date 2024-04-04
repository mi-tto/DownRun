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

	Size mVisibleSize = Director::getInstance()->getVisibleSize(); //ȭ�� �ػ�
	Vec2 mOrigin = Director::getInstance()->getVisibleOrigin(); //�����

public:

	bool isTouch;

	static Scene* createScene();
	virtual bool init();
	void ChangeScnene();
	virtual void onInit(); //�ʱ�ȭ
	virtual void onRelease(); //�޸𸮻���
	virtual void onLoad(); //�ҷ����� ������ �ε�
	virtual bool onTouch(Touch *touch, Event * event);

	CREATE_FUNC(Intro);
};

#endif // __HELLOWORLD_SCENE_H__
