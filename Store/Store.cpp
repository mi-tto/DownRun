#include "Store.h"
#include "Intro.h"
#include "B_Singleton.h"

Scene* Store::createScene()
{
	// auto는 Scene* 과 동일.
	auto scene = Scene::create();

	// 헤더에서 선언해둔 CREATE_FUNC(HelloWorld)으로 HelloWorld::create() 방식의 선언이 가능
	auto layer = Store::create();

	// scene->addchile(layer, 0, -1) 과 동일. 각각 zOrder와 tag의 기본값이다.
	scene->addChild(layer);

	return scene;
}

bool Store::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Store::onTouch, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
	onLoad();

	winSize = Director::getInstance()->getWinSize();

	Spr = Sprite::create("pop.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2));
	Spr->setScale(1.6f);
	Spr->setTag(TAG_SPRITE);
	Spr->setVisible(false);
	this->addChild(Spr, 9);

	item_1 = Sprite::create("yes.png");
	item_1->setScale(0.6f);
	item_1->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 30, mOrigin.y + mVisibleSize.height / 2));
	item_1->setTag(TAG_YES);
	item_1->setVisible(false);
	this->addChild(item_1, 10);


	item_2 = Sprite::create("no.png");
	item_2->setScale(0.6f);
	item_2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + 30, mOrigin.y + mVisibleSize.height / 2));
	item_2->setTag(TAG_NO);
	item_2->setVisible(false);
	this->addChild(item_2, 10);

	coin = UserDefault::getInstance()->getIntegerForKey("COIN");

	CCLOG("%d", coin);

	auto label_3 = Label::createWithBMFont("bitmapfontchinese.fnt", "");
	label_3->setAnchorPoint(Point(1, 1));
	label_3->setPosition(Point(mOrigin.x + mVisibleSize.width / 1.6, mOrigin.y + mVisibleSize.height / 3.4));
	label_3->setTag(TAG_COIN);
	label_3->setScale(0.6);
	this->addChild(label_3, 4);

	this->schedule(schedule_selector(Store::onUpdate));
	return true;
}

void Store::onLoad()
{
	int x = 3.5; // 가로간격 
	int y = 0; //세로간격

	ItemBox();
	auto Spr = Sprite::create("background.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2));
	this->addChild(Spr, 1);

	Spr = Sprite::create("menu.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 40));
	this->addChild(Spr, 2);

	Spr = Sprite::create("coin.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 350));
	this->addChild(Spr, 3);

	Spr = Sprite::create("myitem.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 100, mOrigin.y + mVisibleSize.height - 415));
	this->addChild(Spr, 3);

	Spr = Sprite::create("myitem.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 30, mOrigin.y + mVisibleSize.height - 415));
	this->addChild(Spr, 3);

	Spr = Sprite::create("back.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + 100, mOrigin.y + mVisibleSize.height - 415));
	this->addChild(Spr, 3, TAG_GO_MENU);
}


void Store::ItemBox()
{
	float x = 3.5; // 가로간격 
	float y = 0; //세로간격


	////아이템 그림들

	/* 아이템 태그 이름
	-----------------------------
	|        |        |         |
	|    1   |    2   |    3    |
	|        |        |         |
	-----------------------------
	|        |        |         |
	|   4    |    5   |    6    |
	|        |        |         |
	-----------------------------
	*/
	auto Spr = Sprite::create("itemt.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 130));
	Spr->setScale(1.1f);
	this->addChild(Spr, 2, 1);
	Spr->setTag(TAG_LIFE);

	Spr = Sprite::create("lifeup.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 130));
	Spr->setScale(1.1f);
	this->addChild(Spr, 2, 1);//라이프충전

	auto Spr2 = Sprite::create("itemt.png");
	Spr2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 130));
	Spr2->setScale(1.1f);
	this->addChild(Spr2, 2, 2);
	Spr2->setTag(TAG_SCROLL);

	Spr2 = Sprite::create("scroll.png");
	Spr2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 130));
	Spr2->setScale(1.1f);
	this->addChild(Spr2, 2, 2); //스크롤

	auto Spr3 = Sprite::create("itemt.png");
	Spr3->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 130));
	Spr3->setScale(1.1f);
	this->addChild(Spr3, 2, 3);
	Spr3->setTag(TAG_SCORE);

	Spr3 = Sprite::create("score.png");
	Spr3->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 130));
	Spr3->setScale(1.1f);
	this->addChild(Spr3, 2, 3); //점수 5.19


	Spr = Sprite::create("itemt.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 240));
	Spr->setScale(1.1f);
	this->addChild(Spr, 2, 5);

	Spr = Sprite::create("itemt.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 240));
	Spr->setScale(1.1f);
	this->addChild(Spr, 2, 4);

	Spr = Sprite::create("itemt.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 240));
	Spr->setScale(1.1f);
	this->addChild(Spr, 2, 6);

	/////////아이템 가격들
	Spr = Sprite::create("itemm.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 185));
	Spr->setScale(1.3f);
	this->addChild(Spr, 3);

	auto label = Label::createWithBMFont("bitmapfontchinese.fnt",//6.8
		"30", TextHAlignment::CENTER, 50);
	label->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 185));
	label->setScale(0.4);
	this->addChild(label, 4);


	Spr = Sprite::create("itemm.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 185));
	Spr->setScale(1.3f);
	this->addChild(Spr, 3);

	auto label2 = Label::createWithBMFont("bitmapfontchinese.fnt",//6.8
		"30", TextHAlignment::CENTER, 50);
	label2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 185));
	label2->setScale(0.4);
	this->addChild(label2, 4);

	Spr = Sprite::create("itemm.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 185));
	Spr->setScale(1.3f);
	this->addChild(Spr, 3);

	auto label3 = Label::createWithBMFont("bitmapfontchinese.fnt",//6.8
		"30", TextHAlignment::CENTER, 50);
	label3->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 185));
	label3->setScale(0.4);
	this->addChild(label3, 4);


	Spr = Sprite::create("itemm.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height - 295));
	Spr->setScale(1.3f);
	this->addChild(Spr, 3);

	Spr = Sprite::create("itemm.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 295));
	Spr->setScale(1.3f);
	this->addChild(Spr, 3);

	Spr = Sprite::create("itemm.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 + mVisibleSize.width / x, mOrigin.y + mVisibleSize.height - 295));
	Spr->setScale(1.3f);
	this->addChild(Spr, 3);

}

bool Store::onTouch(Touch *touch, Event * event)
{
	Point location = touch->getLocation();

	auto Sprback = (Sprite*)this->getChildByTag(TAG_GO_MENU);
	Rect MENU = Sprback->getBoundingBox();

	//===아이템===
	auto life = (Sprite*)this->getChildByTag(TAG_LIFE);
	Rect liferect = life->getBoundingBox();

	auto scroll = (Sprite*)this->getChildByTag(TAG_SCROLL);
	Rect scrollrect = scroll->getBoundingBox();

	auto score = (Sprite*)this->getChildByTag(TAG_SCORE);//5.19
	Rect scorerect = score->getBoundingBox();

	//==버튼==
	Rect rectyes = item_1->getBoundingBox();
	Rect rectno = item_2->getBoundingBox();

	if (MENU.containsPoint(location))//뒤로가기
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(0.7,
			Intro::createScene());
		Director::getInstance()->replaceScene(scene);//5.19
	}

	if (coin >= 30)//5.30
	{
		if (rectyes.containsPoint(location))
		{
			Spr->setVisible(false);
			item_1->setVisible(false);
			item_2->setVisible(false);
			if (lifeyes == true)
			{
				dataSingleton::getInstance()->buy = true;
				setlife = true;
				lifeyes = false;
				UserDefault::getInstance()->setIntegerForKey("COIN", coin - 30);
				coin = coin - 30;
			}

			if (scrollyes == true)
			{
				dataSingleton::getInstance()->buy = true;

				setscroll = true;
				scrollyes = false;
				UserDefault::getInstance()->setIntegerForKey("COIN", coin - 30);
				coin = coin - 30;
			}

			if (scoreyes == true)//5.19
			{
				dataSingleton::getInstance()->buy = true;

				setscore = true;
				scoreyes = false;
				UserDefault::getInstance()->setIntegerForKey("COIN", coin - 30);
				coin = coin - 30;
			}
		}
	}

	if (rectno.containsPoint(location))//5.25
	{
		Spr->setVisible(false);
		item_1->setVisible(false);
		item_2->setVisible(false);
		if (lifeyes == true)
		{
			lifeyes = false;
		}

		if (scrollyes == true)
		{

			scrollyes = false;
		}

		if (scoreyes == true)
		{

			scoreyes = false;
		}
	}

	if (liferect.containsPoint(location))//라이프충전
	{
		Spr->setVisible(true);
		item_1->setVisible(true);
		item_2->setVisible(true);

		lifeyes = true;
	}

	if (scrollrect.containsPoint(location))//스크롤
	{
		Spr->setVisible(true);
		item_1->setVisible(true);
		item_2->setVisible(true);

		scrollyes = true;
	}

	if (scorerect.containsPoint(location))//스코어 5.19
	{
		Spr->setVisible(true);
		item_1->setVisible(true);
		item_2->setVisible(true);

		scoreyes = true;
	}

	return true;
}


void Store::onUpdate(float delta)
{
	SetCoin();
	if (dataSingleton::getInstance()->buy == true)
	{

		if (count == 0)
		{
			if (setlife == true)
			{
				Sprite *Spr = Sprite::create("lifeup.png");
				Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 100, mOrigin.y + mVisibleSize.height - 415));
				Spr->setScale(0.8f);
				this->addChild(Spr, 7);
				dataSingleton::getInstance()->buy = false;
				dataSingleton::getInstance()->life = true;
				setlife = false;
				count++;

			}

			if (setscroll == true)
			{
				Sprite *Spr = Sprite::create("scroll.png");
				Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 100, mOrigin.y + mVisibleSize.height - 415));
				Spr->setScale(0.8);
				this->addChild(Spr, 7);
				dataSingleton::getInstance()->buy = false;
				dataSingleton::getInstance()->scroll = true;
				setscroll = false;
				count++;
			}

			if (setscore == true)//5.19
			{
				Sprite *Spr = Sprite::create("score.png");
				Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 100, mOrigin.y + mVisibleSize.height - 415));
				Spr->setScale(0.8);
				this->addChild(Spr, 100);
				dataSingleton::getInstance()->buy = false;
				dataSingleton::getInstance()->score = true;
				setscore = false;
				count++;
			}
		}
		else if (count == 1)
		{
			if (setlife == true)
			{
				Sprite *Spr2 = Sprite::create("lifeup.png");
				Spr2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 30, mOrigin.y + mVisibleSize.height - 415));
				Spr2->setScale(0.8f);
				this->addChild(Spr2, 7);
				dataSingleton::getInstance()->buy = false;
				dataSingleton::getInstance()->life2 = true;
				setlife = false;
				count--;
			}


			if (setscroll == true)
			{
				Sprite *Spr2 = Sprite::create("scroll.png");
				Spr2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 30, mOrigin.y + mVisibleSize.height - 415));
				Spr2->setScale(0.8);
				this->addChild(Spr2, 7);
				dataSingleton::getInstance()->buy = false;
				dataSingleton::getInstance()->scroll2 = true;
				setscroll = false;
				count--;

			}

			if (setscore == true)
			{
				Sprite *Spr2 = Sprite::create("score.png");//5.19
				Spr2->setPosition(Point(mOrigin.x + mVisibleSize.width / 2 - 30, mOrigin.y + mVisibleSize.height - 415));
				Spr2->setScale(0.8);
				this->addChild(Spr2, 7);
				dataSingleton::getInstance()->buy = false;
				dataSingleton::getInstance()->score2 = true;
				setscore = false;
				count--;

			}

		}

	}

	SetCoin();//5.30
}

void Store::SetCoin()//5.30
{
	auto label = (Label*)this->getChildByTag(TAG_COIN);
	label->setString(StringUtils::format("%d", coin));
}