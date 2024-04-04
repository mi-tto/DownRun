#ifndef __STAGE_2_LAYER_H__
#define __STAGE_2_LAYER_H__

#include "cocos2d.h"
#include "StageIdx.h"

USING_NS_CC;

#define TAG_SPRITE_PUNCH			60000

enum PUNCH_DIR
{
	_LEFT,
	_RIGHT
};

class Stage2Layer :public StageIdx
{
private:

	// + 컨베이어 / 주먹

	int mStage_1_ObstaclePer = 85;

	float mPunchTime;
	float mPunchSpeed;

	Sprite* mPunch;
	PUNCH_DIR mPunchDir;

	bool isInit;
	bool isOnceAttack;
	bool isTick;

public:
	Stage2Layer();

	virtual void onInit();
	virtual void onActionFade(){}
	virtual Sprite* onMakeObstacle(Sprite* spr, int _bType, bool* _isobstacle, bool isfalling);
	virtual void onUpdate(float delta, Point& cPos, Size& visible);

	virtual int Get_Stage_idx()
	{
		return 2;
	}

	void SetObstaclePer()
	{
		mObstaclePer = 45;
	}

	Rect Get_PunchRect()
	{
		return mPunch->getBoundingBox();
	}

	void onBGInit();
	void onDataInit();
	void onRelease();
	void onMakePunch(Point& cPos, Size& visible);

	void onPunchCallBack();

};

#endif