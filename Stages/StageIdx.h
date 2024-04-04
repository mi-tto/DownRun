#ifndef __STAGE_IDX_H__
#define __STAGE_IDX_H__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_OBSTACLE_THORN			3000
#define TAG_OBSTACLE_TRAP			4000
#define TAG_OBSTACLE_CONTEINER		5000

class StageIdx : public Layer
{
protected:
	Layer* bgLayer;

	Sprite* mObstacleSpr;

	Vec2 mOrigin;

	int m_ObstacleType;
	int mObstaclePer;
	int mThornPer;

	bool isStartInit;

	float m_x;
	float m_y;

public:

	StageIdx()
	{
		mObstaclePer = 40;
		mThornPer = 75;
	}

	CREATE_FUNC(StageIdx);

	virtual bool init();
	virtual void onInit(){}
	virtual void onActionFade(){}
	virtual Sprite* onMakeObstacle(Sprite* spr, int _bType, bool* _isobstacle, bool isfallin);
	virtual void onUpdate(float delta, Point& cPos, Size& visible){}

	virtual int Get_Stage_idx()
	{
		return 0;
	}

	virtual Rect Get_PunchRect()
	{
		return Rect::ZERO;
	}
};

#endif