#ifndef __STORE_H__
#define __STORE_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_GO_MENU		0

#define TAG_ITEM_ONE	100	
#define TAG_NO          200

#define TAG_YES         300
#define TAG_YES2        350
#define TAG_LIFE        400
#define TAG_SPRITE      500
#define TAG_SCROLL      600
#define TAG_COIN        800//5.30

class Store : public Layer
{
private:
	Size mVisibleSize = Director::getInstance()->getVisibleSize(); //화면 해상도
	Vec2 mOrigin = Director::getInstance()->getVisibleOrigin(); //정가운데

	Size winSize;
	int count = 0;
	Sprite* Spr;
	Sprite* item_1;
	Sprite* item_2;
	bool lifeyes = false;
	bool scrollyes = false;
	bool setlife = false;
	bool setscroll = false;
	bool scoreyes = false;//5.19
	bool setscore = false;//5.19

	int coin;

public:
	static Scene* createScene();
	virtual bool init();
	virtual void ItemBox();
	bool onTouch(Touch *touch, Event * unused_event);

	void onUpdate(float delta);
	void Visible();
	void UnVisible();
	void Visible2();
	void UnVisible2();
	void SetCoin();//5.30

	virtual void onLoad(); //불러오는 데이터 로드
	CREATE_FUNC(Store);
};

#endif