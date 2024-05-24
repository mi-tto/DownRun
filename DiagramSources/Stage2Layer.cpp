#include "Stage2Layer.h"
#include "SimpleAudioEngine.h"//5.19
#include "B_Singleton.h"

using namespace CocosDenshion;//5.19

Stage2Layer::Stage2Layer()
{
	onDataInit();

	if (isStartInit == true)
	{
		SimpleAudioEngine::getInstance()->
			playBackgroundMusic("bgm_03.mp3");//5.19

		dataSingleton::getInstance()->stagechange = true;
	}
}

void Stage2Layer::onInit()
{
	if (isStartInit)
	{
		SetObstaclePer();

		bgLayer = Layer::create();
		this->addChild(bgLayer);

		auto spr1 = Sprite::create("stage3.png", Rect(0, 0, 320, 480));
		spr1->setAnchorPoint(Point(0, 1));
		spr1->setPosition(Point(0, 480));
		spr1->setOpacity(0);
		auto action = FadeIn::create(2.0);;
		spr1->runAction(action);
		bgLayer->addChild(spr1, 0);

		auto spr2 = Sprite::create("stage3.png");
		spr2->setAnchorPoint(Point(0, 1));
		spr2->setPosition(Point(0, 0));
		bgLayer->addChild(spr2, 0);

		auto action_1 = MoveBy::create(10, Point(0, 960));
		auto action_2 = CallFunc::create(CC_CALLBACK_0(Stage2Layer::onBGInit, this));
		auto action_3 = Sequence::create(action_1, action_2, NULL);
		bgLayer->runAction(action_3);

		isStartInit = false;
	}
}

void Stage2Layer::onDataInit()
{
	m_x = 0;
	m_y = 0;

	isStartInit = true;
	isInit = false;
	isOnceAttack = false;
	isTick = true;

	mPunchTime = rand() % 6 + 15;
	mPunchSpeed = 300;

	mPunch = Sprite::create("punch.png");
	mPunch->setAnchorPoint(Point(0, 1));
	mPunch->setPosition(Point(-150, -150));
	this->addChild(mPunch, 20);
}

void Stage2Layer::onBGInit()
{
	auto action_0 = Place::create(Point(0, 0));
	auto action_1 = MoveBy::create(10, Point(0, 960));
	auto action_2 = Sequence::create(action_0, action_1, NULL);
	auto action_3 = RepeatForever::create(action_2);
	bgLayer->runAction(action_3);
}

Sprite* Stage2Layer::onMakeObstacle(Sprite* spr, int _bType, bool* _isobstacle, bool isfalling)
{
	if (!isfalling)
	{
		int ran = rand() % 100;

		if (mObstaclePer >= ran)
		{
			*_isobstacle = true;

			ran = rand() % 100;

			if (mStage_1_ObstaclePer >= ran)
			{
				if (mThornPer >= ran)
				{
					mObstacleSpr = Sprite::create("thorn.png");
					mObstacleSpr->setAnchorPoint(Point(1, 0));
					mObstacleSpr->setTag(TAG_OBSTACLE_THORN);
					m_ObstacleType = TAG_OBSTACLE_THORN;

					int _ran = 1 + rand() % (_bType + 2);
					int x = spr->getPosition().x + (mObstacleSpr->getContentSize().width * _ran);
					mObstacleSpr->setPosition(Point(x, spr->getPosition().y));
					return mObstacleSpr;
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
					return mObstacleSpr;
				}
			}
			else
			{
				return NULL;
			}
		}
	}
	return NULL;
}

void Stage2Layer::onUpdate(float delta, Point& cPos, Size& visible)
{
	if (isTick)
		mPunchTime -= delta;

	// 생성
	if (mPunchTime <= 0 && !isInit && isTick)
	{
		isTick = false;
		isInit = true;
		onMakePunch(cPos, visible);
	}

	if (isInit)
	{
		switch (mPunchDir)
		{
			// 05.26
		case _LEFT:
			{
					  auto action_0 = MoveTo::create(0.5, Point(0, m_y));
					  auto action_1 = EaseExponentialInOut::create(action_0);

					  auto action_2 = DelayTime::create(0.2);

					  auto action_3 = MoveTo::create(0.5, Vec2(-mPunch->getContentSize().width - 100, m_y));

					  auto action_4 = CallFunc::create(CC_CALLBACK_0(Stage2Layer::onPunchCallBack, this));
					  auto action_5 = Sequence::create(action_1, action_2, action_3, action_4, NULL);

					  mPunch->runAction(action_5);

					  isInit = false;
			}
				break;
		case _RIGHT:
			{
					   auto action_0 = MoveTo::create(0.5, Point(visible.width - (mPunch->getContentSize().width), m_y));
					   auto action_1 = EaseExponentialInOut::create(action_0);

					   auto action_2 = DelayTime::create(0.2);

					   auto action_3 = MoveTo::create(0.5, Vec2(visible.width + 100, m_y));

					   auto action_4 = CallFunc::create(CC_CALLBACK_0(Stage2Layer::onPunchCallBack, this));
					   auto action_5 = Sequence::create(action_1, action_2, action_3, action_4, NULL);

					   mPunch->runAction(action_5);

					   isInit = false;
			}
				break;
		default:
			break;
		}
	}
}

void Stage2Layer::onMakePunch(Point& cPos, Size& visible)
{
	// 캐릭터의 x 위치가

	// 좌측일 경우
	if (cPos.x <= visible.width / 2)
	{
		mPunchDir = PUNCH_DIR::_LEFT;

		m_x = 0 - mPunch->getContentSize().width - 100;

		// 스프라이트 height 크기 ~ (화면 가로 1/2 + 스프라이트 height 크기)
		m_y = rand() % (int)(1 + (visible.height / 2)) + (mOrigin.y + mPunch->getContentSize().height);

		mPunch->setPosition(m_x, m_y);
		
		auto action = FlipX::create(false);
		mPunch->runAction(action);
	}
//	 우측일 경우
	else
	{
		mPunchDir = PUNCH_DIR::_RIGHT;

		m_x = visible.width + 100;
		m_y = rand() % (int)(1 + (visible.height / 2)) + (mOrigin.y + mPunch->getContentSize().height);

		mPunch->setPosition(m_x, m_y);
		
		auto action = FlipX::create(true);
		mPunch->runAction(action);
	}
}

void Stage2Layer::onPunchCallBack()
{
	mPunchTime = rand() % 6 + 15;
	isTick = true;
}