#ifndef __STAGE_1_LAYER_H__
#define __STAGE_1_LAYER_H__

#include "cocos2d.h"
#include "StageIdx.h"

USING_NS_CC;

class Stage1Layer :public StageIdx
{
private:

	Layer* bgLayer;
	Sprite* mSpr1;
	Sprite* mSpr2;

public:
	Stage1Layer();
	virtual void onInit();
	virtual void onActionFade();
	virtual Sprite* onMakeObstacle(Sprite* spr, int _bType, bool* _isobstacle, bool isfallin);
	virtual void onUpdate(float delta, Point& cPos, Size& visible){}

	virtual int Get_Stage_idx()
	{
		return 1;
	}

	virtual Rect Get_PunchRect()
	{
		return Rect::ZERO;
	}

	void onDataInit();
	void onRelease();
};

#endif