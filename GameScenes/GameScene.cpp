#include "GameScene.h"
#include "Stage1Layer.h"
#include "Stage2Layer.h"
#include "SimpleAudioEngine.h"//5.19
#include "B_Singleton.h"//5.19
#include "PopLayerScene.h"
#include "Ending.h"

using namespace CocosDenshion;//5.19


GameScene* GameScene::s_ptr;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();

	s_ptr = GameScene::create();

	scene->addChild(s_ptr);

    // return the scene
    return scene;
}

bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	restart = false;
	isdead = false;

	isFirst = true;

	mCharacter = NULL;
	mBlock = NULL;

	////////////////6.1)
	Time = 0;
	Sec = 0;
	Min = 0;
	Mil = 0;
	check = false;
	/////////////////////////////////////////////////(6.1)
	srand(time(NULL));
    
	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////

	mLayer = new Stage1Layer;
	mLayer->onInit();
	this->addChild(mLayer, 0);

	onGameDataInit();
	onUiInit();

	this->scheduleOnce(schedule_selector(GameScene::scheduleCallBack), 1.0);
	this->schedule(schedule_selector(GameScene::onUpdate));

	SimpleAudioEngine::getInstance()->
		playBackgroundMusic("bgm_01.mp3");//5.19

    return true;
}

void GameScene::onGameDataInit()
{
	mCurState = STAGE_NUM::STAGE_1;
	isMinHp = false;
	isStageChange = false;

	mItem = Item::create();
	mItem->setZOrder(30);
	this->addChild(mItem);

	mCharacter = Character::create();
	this->addChild(mCharacter, 2);
	mHpMinusNum = mCharacter->onGetHp() - 1;
	mHpPlusNum = mCharacter->onGetHp() + 1;

	mBlock = new Block*[blockMAX];
	for (int i = startBlockNum; i < blockMAX; i++)
	{
		int random = rand() % 3;
		mBlock[i] = Block::create();
		mBlock[i]->onDataInit(random, i * 4 + 1);
		mBlock[i]->setTag(i);
		this->addChild(mBlock[i], 1);
	}
}

void GameScene::onUiInit()
{
	// 시간 
	auto SprTime1 = Sprite::create("timebar.png");
	SprTime1->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 6, mOrigin.y + mVisibleSize.height - 20));
	SprTime1->setOpacity(0);
	SprTime1->setScale(0.75f);
	this->addChild(SprTime1, 2);
	auto action = FadeTo::create(5.0,180);
	SprTime1->runAction(action);

	// 코인
	auto SprTime2 = Sprite::create("timebar.png");
	SprTime2->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 6, mOrigin.y + mVisibleSize.height - 50));
	SprTime2->setOpacity(0);
	SprTime2->setScale(0.75f);
	this->addChild(SprTime2, 2);
	action = FadeTo::create(5.0, 180);
	SprTime2->runAction(action);
	
	// 체력
	int x = 20;//가로 간격

	auto SprHp1 = Sprite::create("heart2.png");
	SprHp1->setPosition(Point(mOrigin.x + mVisibleSize.width / 20, mOrigin.y + mVisibleSize.height - 70));
	SprHp1->setScale(0.02f);
	SprHp1->setOpacity(0);
	SprHp1->setTag(HP_ONE);
	this->addChild(SprHp1, 10);
	action = FadeIn::create(3.0);
	SprHp1->runAction(action);


	auto SprHp2 = Sprite::create("heart2.png");
	SprHp2->setPosition(Point(mOrigin.x + mVisibleSize.width / 20 + x, mOrigin.y + mVisibleSize.height - 70));
	SprHp2->setScale(0.02f);
	SprHp2->setOpacity(0);
	SprHp2->setTag(HP_TWO);
	this->addChild(SprHp2, 10);
	action = FadeIn::create(3.0);
	SprHp2->runAction(action);

	auto SprHp3 = Sprite::create("heart2.png");
	SprHp3->setPosition(Point(mOrigin.x + mVisibleSize.width / 20+ (x * 2), mOrigin.y + mVisibleSize.height - 70));
	SprHp3->setScale(0.02f);
	SprHp3->setOpacity(0);
	SprHp3->setTag(HP_THREE);
	this->addChild(SprHp3, 10);
	action = FadeIn::create(3.0);
	SprHp3->runAction(action);

	mHpTagNum = HP_THREE;

	//일시정지
	auto pause_button = Sprite::create("i_pause.png");
	auto item = MenuItemSprite::create(pause_button, NULL, CC_CALLBACK_1(GameScene::pause, this));
	auto menu = Menu::create(item, NULL);
	menu->setOpacity(0);
	menu->setScale(0.9f);
	menu->setPosition(Point(mVisibleSize.width / 2 - 15, mVisibleSize.height - 55));
	this->addChild(menu, 3);
	action = FadeIn::create(3.0);
	menu->runAction(action);

	auto label_0 = Label::createWithTTF("", "ssf.ttf", 15); // 분을 적어줄 라벨
	label_0->setAnchorPoint(Point(0, 1));
	label_0->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 8 - 60, mOrigin.y + mVisibleSize.height - 14));
	label_0->setOpacity(0);
	label_0->setTag(TAG_MIN);
	label_0->setColor(Color3B::WHITE);
	this->addChild(label_0, 3);
	auto action1 = FadeIn::create(5.0);
	label_0->runAction(action1);


	auto label_1 = Label::createWithTTF("", "ssf.ttf", 15); // 초를 적어줄 라벨
	label_1->setAnchorPoint(Point(1, 1));
	label_1->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 8, mOrigin.y + mVisibleSize.height - 14));
	label_1->setOpacity(0);
	label_1->setTag(TAG_SEC);
	label_1->setColor(Color3B::WHITE);
	this->addChild(label_1, 3);
	auto action2 = FadeIn::create(5.0);
	label_1->runAction(action2);


	auto label_2 = Label::createWithTTF("", "ssf.ttf", 15); //밀리세컨드를 적어줄 라벨
	label_2->setAnchorPoint(Point(1, 1));
	label_2->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 8 + 30, mOrigin.y + mVisibleSize.height - 14));
	label_2->setOpacity(0);
	label_2->setTag(TAG_MIL);
	label_2->setColor(Color3B::WHITE);
	this->addChild(label_2, 3);
	auto action3 = FadeIn::create(5.0);
	label_2->runAction(action3);


	auto label_3 = Label::createWithTTF("", "ssf.ttf", 15); // 점수를 적어줄 라벨
	label_3->setAnchorPoint(Point(1, 1));
	label_3->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 20, mOrigin.y + mVisibleSize.height - 45));
	label_3->setOpacity(0);
	label_3->setTag(TAG_SCORE);
	label_3->setColor(Color3B::WHITE);
	this->addChild(label_3, 3);
	auto action4 = FadeIn::create(5.0);
	label_3->runAction(action4);
}

void GameScene::onChangeStageLayer()
{
	switch (mCurState)
	{
	case STAGE_2:
	{
					mLayer = new Stage2Layer;
	}
		break;
	case STAGE_3:
	{

	}
		break;
	default:
		break;
	}
}

void GameScene::onUpdate(float delta)
{
	int _hp = mCharacter->onGetHp();

	if ((!CCDirector::sharedDirector()->isPaused()) && isdead == false)//일시정지가 아니고 죽은상태가 아닐시 시간더하기
	{
		Time = Time + delta;
		Sec = (int)Time;
		Mil = Time - Sec;

		if (Sec == 60)
		{
			Sec = 0;
			Min++;
		}
	}

	//1~2스테이지 점수 출력 방식
	if (mCurState == STAGE_NUM::STAGE_1)
	{
		AllScore = (Sec * 10) + (Min * 600);
	}
	if (mCurState == STAGE_NUM::STAGE_2)
	{
		AllScore = (Sec * 15) + (Min * 900);
	}

	//////////////////////////////////////////////////////////////////////

	if (isStart == true && isdead == false)//게임시작했고 죽지않았고
	{
		if ((mCharacter->onGetypos() > mVisibleSize.height) || (mCharacter->onGetypos() <= 0 - mCharacter->getContentSize().height / 5))//캐릭터가 젤위 젤아래에 닿았을시
		{
			isdead = true; //죽은 상태로 바꾸고 체력을 0으로 바꾸고 엔딩씬 출력
			mCharacter->SetHp(0);
			EndingScene();
		}
	}

	////////////////////////////////////////////(6.1)

	if (_hp <= 0 && isdead == false)
	{
		isdead = true;
		this->scheduleOnce(schedule_selector(GameScene::scheduleCallBack2), 3.0);//장애물에 당할때도 엔딩나오게
	}

	if (isStageChange)
	{
		isStageChange = false;
		mLayer->onActionFade();
		onChangeStageLayer();
		mLayer->onInit();
		this->addChild(mLayer, 0);
	}

	Point pos;
	pos = mCharacter->Get_MyPosition();

	mLayer->onUpdate(delta, pos, mVisibleSize);
	for (int i = startBlockNum; i < blockMAX; i++)
	{
		if (i == 0)
			mBlock[i]->onUpdate(delta, mBlock[blockMAX - 1]);
		else
			mBlock[i]->onUpdate(delta, mBlock[i - 1]);
	}

	if (!isMinHp)
		mCharacter->onUpdate(delta, mBlock, startBlockNum, blockMAX);
	onDrawHp();
	Score();
}

void GameScene::EndingScene()
{
	if (check == false)
	{
		CCLOG("ending scene print");
		coin = UserDefault::getInstance()->getIntegerForKey("COIN"); // 코인 저장
	UserDefault::getInstance()->setIntegerForKey("COIN", (AllScore / 10) + coin);
		//UserDefault::getInstance()->flush();
		coin = UserDefault::getInstance()->getIntegerForKey("COIN");
		check = true;
	}

	auto Spr = Sprite::create("ending.png", Rect(0, 0, 320, 480));
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2));
	this->addChild(Spr, 30);

	/////////////////////////////////////////////////////////////////////////////////(6.9) - 엔딩씬 글꼴 위치 수정

	auto label = Label::createWithTTF("", "ssf.ttf", 50, Size(200, mOrigin.y + mVisibleSize.height / 2), TextHAlignment::LEFT); //점수를 적어줄 라벨
	label->setAnchorPoint(Point(1, 1));
	label->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / 1.6, mOrigin.y + mVisibleSize.height / 1.95));
	label->setColor(Color3B::WHITE);
	this->addChild(label, 40);
	label->setString(StringUtils::format("%d", AllScore));


	auto label2 = Label::createWithTTF("", "ssf.ttf", 50, Size(200, mOrigin.y + mVisibleSize.height / 10), TextHAlignment::LEFT); //코인을 적어줄 라벨
	label2->setAnchorPoint(Point(1, 1));
	label2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / 1.6, mOrigin.y + mVisibleSize.height / 2.5));
	label2->setColor(Color3B::YELLOW);
	this->addChild(label2, 50);
	label2->setString(StringUtils::format("%d", AllScore / 10));
	//label2->setString(StringUtils::format("%d", coin));

	///////////////////////////////////////////////////////////////////////////////////////

	auto layer = Ending::CreateScene(); //엔딩씬 출력
	this->addChild(layer, 30);
}

void GameScene::Score()
{

	int _hp = mCharacter->onGetHp();
	int hpup = mItem->onGet_HpUse();

	if (_hp > 0)
	{
		this->schedule(schedule_selector
			(GameScene::resetscore), 10.0);//스코어아이템을 사용하면 10초동안 2배로점수획득
	}

	SetScore();

	SetSec();
	SetMin();
	SetMil();
}

void GameScene::pause(Ref *sender)
{
	CCDirector::sharedDirector()->pause();
	auto layer = PopLayer::createScene();
	this->addChild(layer, 30);

	check = true;
}

void GameScene::SetSec()
{
	auto label = (Label*)this->getChildByTag(TAG_SEC);
	label->setString(StringUtils::format("%02d :", Sec));

	if (Sec >= 60 && mCurState == STAGE_NUM::STAGE_1)
	{
		isStageChange = true;
		mCurState = STAGE_NUM::STAGE_2;
	}
}

void GameScene::SetMin()
{
	auto label = (Label*)this->getChildByTag(TAG_MIN);
	label->setString(StringUtils::format("%02d : ", Min));
}

void GameScene::SetMil()
{
	auto label = (Label*)this->getChildByTag(TAG_MIL);
	label->setString(StringUtils::format("%3d", (int)(Mil * 1000)));
}

void GameScene::SetScore()
{
	auto label = (Label*)this->getChildByTag(TAG_SCORE);
	label->setString(StringUtils::format("%d", AllScore));
}

void GameScene::onDrawHp()
{
	int _hp = mCharacter->onGetHp();
	int hpup = mItem->onGet_HpUse();

	if (isMinHp)
		return;

	if (mCharacter->GetIsDamaged())
	{
		int TagValue = _hp * 10 + 10;

		auto spr = (Sprite*)this->getChildByTag(TagValue);
		spr->setVisible(false);


		if (_hp <= 0)
		{
			isMinHp = true;
			mCharacter->onDieMove();
		}
		else
		{
			mCharacter->SetIsDamaged(false);
		}
	}
	if (hpup == true && _hp != mCharacter->onGetMaxHp()) {

		int TagValue = _hp * 10 + 10;

		auto spr = (Sprite*)this->getChildByTag(TagValue);
		spr->setVisible(true);

		mCharacter->AddHp();


		mItem->onSet_HpUse(false);

	}
	return;
}

void GameScene::scheduleCallBack(float delta)
{
	isStart = true;
}

void GameScene::scheduleCallBack2(float delta)
{
	EndingScene();
}

void GameScene::resetscore(float delta)//5.19
{
	dataSingleton::getInstance()->scoreup = false;
}

GameScene::~GameScene()
{

}