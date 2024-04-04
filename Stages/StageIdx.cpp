#include "StageIdx.h"

bool StageIdx::init()
{
	if (!Layer::init())
	{
		return false;
	}

	mOrigin = Director::getInstance()->getVisibleOrigin();

	return true;
}

Sprite* StageIdx::onMakeObstacle(Sprite* spr, int _bType, bool* _isobstacle, bool isfallin)
{
	Sprite* _spr = NULL;
	return _spr;
}