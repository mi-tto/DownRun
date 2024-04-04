#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

USING_NS_CC;

#define ITEM_HP 10
#define ITEM_SCROLL 20

class Item : public Layer
{
protected:

	Sprite* mSpr;
	Size mVisibleSize;
	Vec2 mOrigin;

	bool hpuse;
	bool scrolluse;
	bool scoreuse;//5.19
	bool dustuse;//5.25
	bool randombox;//5.25
	bool randombox2;//5.25
	bool random;//5.25
	bool space;//5.25
	bool space2;//5.25
	int ran;//5.25

	bool rect = false;
	bool rect2 = false;
	Sprite* spr_life;
	Sprite* spr_scroll;
	Sprite* spr_life2;
	Sprite* spr_scroll2;
	Sprite* spr_score;
	Sprite* spr_score2;
	Sprite* spr_ranbox;//5.25
	Sprite* spr_ranbox2;//5.25
	Sprite* spr_dust;//5.25
	Sprite* spr_dust2;//5.25
	Sprite* spr;

	Sprite* spr_speed;//5.30
	Sprite* spr_speed2;//5.30

public:

	virtual bool init();
	CREATE_FUNC(Item);

	void onDataInit();

	bool onGet_ScrollUse()
	{
		return scrolluse; 
	}
	
	//5.19
	void onSet_ScrollUse(bool b)
	{
		scrolluse = b;
	}

	bool onGet_HpUse()
	{
		return hpuse;
	}

	void onSet_HpUse(bool b)
	{
		hpuse = b;
	}

	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	void onUpdate(float delta);
	void resetRandom(float delta);//5.25
	void setDust();//5.25
	void resetDust(Ref *sender);//5.25
	
};

#endif
