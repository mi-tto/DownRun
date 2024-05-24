#include "Stage1Layer.h"

Stage1Layer::Stage1Layer()
{
	isStartInit = true;

	m_x = 0;
	m_y = 0;
}

void Stage1Layer::onInit()
{
	if (isStartInit)
	{
		bgLayer = Layer::create();
		this->addChild(bgLayer);

		mSpr1 = Sprite::create("bg.png", Rect(0, 0, 320, 480));
		mSpr1->setAnchorPoint(Point(0, 1));
		mSpr1->setPosition(Point(0, 480));
		bgLayer->addChild(mSpr1, 0);

		mSpr2 = Sprite::create("bg.png");
		mSpr2->setAnchorPoint(Point(0, 1));
		mSpr2->setPosition(Point(0, 0));
		bgLayer->addChild(mSpr2, 0);

		auto action_0 = MoveBy::create(10, Point(0, 960));
		auto action_1 = Place::create(Point(0, 0));
		auto action_2 = Sequence::create(action_0, action_1, NULL);
		auto action_3 = RepeatForever::create(action_2);
		bgLayer->runAction(action_3);

		isStartInit = false;
	}
}

void Stage1Layer::onActionFade()
{
	auto action0 = FadeOut::create(15.0);
	auto action1 = CallFunc::create(CC_CALLBACK_0(Stage1Layer::onRelease, this));
	auto action2 = Sequence::create(action0, action1, NULL);
	mSpr2->runAction(action2);
}

void Stage1Layer::onRelease()
{
	this->removeAllChildren();
	mSpr1 = NULL;
	mSpr2 = NULL;
}

// 장애물 생성 
Sprite* Stage1Layer::onMakeObstacle(Sprite* spr, int _bType, bool* _isobstacle, bool isfalling)
{
	if (!isfalling)
	{
		int ran = rand() % 100;

		if (mObstaclePer >= ran)
		{
			*_isobstacle = true;

			ran = rand() % 100;

			if (mThornPer >= ran)
			{
				mObstacleSpr = Sprite::create("thorn.png");
				mObstacleSpr->setAnchorPoint(Point(1, 0));
				mObstacleSpr->setTag(TAG_OBSTACLE_THORN);
				m_ObstacleType = TAG_OBSTACLE_THORN;

				int _ran = 1 + rand() % (_bType + 2);
				int x = spr->getPosition().x + (mObstacleSpr->getContentSize().width * _ran);
				mObstacleSpr->setPosition(Point(x, spr->getPosition().y));
			}
			else
			{

				mObstacleSpr = Sprite::create("fall.png");
				mObstacleSpr->setAnchorPoint(Point(1, 1));
				mObstacleSpr->setTag(TAG_OBSTACLE_TRAP);
				m_ObstacleType = TAG_OBSTACLE_TRAP;

				int _ran = 1 + rand() % (_bType + 2); // 1, 2
				int x = spr->getPosition().x + (mObstacleSpr->getContentSize().width * _ran);
				mObstacleSpr->setPosition(Point(x, spr->getPosition().y - spr->getContentSize().height));

			}

			return mObstacleSpr;
		}
	}
	
	return NULL;
}