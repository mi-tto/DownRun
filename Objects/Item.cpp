#include "Item.h"
#include "B_Singleton.h"

bool Item::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();

	onDataInit();

	this->schedule(schedule_selector(Item::onUpdate));

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2
		(Item::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->
		addEventListenerWithFixedPriority(listener, 1);

	/* 아이템 */
	auto SprItem1 = Sprite::create("item.png");
	SprItem1->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));
	SprItem1->setOpacity(0);
	SprItem1->setScale(0.7);
	SprItem1->setTag(150);
	this->addChild(SprItem1, 4);
	auto action = FadeTo::create(5.0, 30);
	SprItem1->runAction(action);

	auto SprItem2 = Sprite::create("item.png");
	SprItem2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));
	SprItem2->setOpacity(0);
	SprItem2->setScale(0.7);
	SprItem2->setTag(250);
	this->addChild(SprItem2, 4);
	action = FadeTo::create(5.0, 30);
	SprItem2->runAction(action);

	//라이프//
	if (dataSingleton::getInstance()->life == true)
	{
		spr_life = Sprite::create("lifeup.png");
		spr_life->setPosition(Point(mOrigin.x + mVisibleSize.width / 9.5, mOrigin.y + mVisibleSize.height - 40));
		spr_life->setScale(0.04f);

		this->addChild(spr_life, 20);
	}

	if (dataSingleton::getInstance()->life2 == true)
	{
		spr_life2 = Sprite::create("lifeup.png");
		spr_life2->setPosition(Point(mOrigin.x + mVisibleSize.width / 3.5, mOrigin.y + mVisibleSize.height - 40));


		this->addChild(spr_life2, 20);
	}
	//스크롤//
	if (dataSingleton::getInstance()->scroll == true)
	{
		spr_scroll = Sprite::create("scroll.png");
		spr_scroll->setPosition(Point(mOrigin.x + mVisibleSize.width / 9.5, mOrigin.y + mVisibleSize.height - 40));


		this->addChild(spr_scroll, 20);
	}
	if (dataSingleton::getInstance()->scroll2 == true)
	{
		spr_scroll2 = Sprite::create("scroll.png");
		spr_scroll2->setPosition(Point(mOrigin.x + mVisibleSize.width / 3.5, mOrigin.y + mVisibleSize.height - 40));


		this->addChild(spr_scroll2, 20);
	}

	//스코어//

	if (dataSingleton::getInstance()->score == true)
	{
		spr_score = Sprite::create("score.png");
		spr_score->setPosition(Point(mOrigin.x + mVisibleSize.width / 9.5, mOrigin.y + mVisibleSize.height - 40));


		this->addChild(spr_score, 20);
	}
	if (dataSingleton::getInstance()->score2 == true)
	{
		spr_score2 = Sprite::create("score.png");
		spr_score2->setPosition(Point(mOrigin.x + mVisibleSize.width / 3.5, mOrigin.y + mVisibleSize.height - 40));


		this->addChild(spr_score2, 20);
	}

	if (dataSingleton::getInstance()->life == true || dataSingleton::getInstance()->scroll == true || dataSingleton::getInstance()->score == true)//5.25 
	{
		space = true;
	}


	if (dataSingleton::getInstance()->life2 == true || dataSingleton::getInstance()->scroll2 == true || dataSingleton::getInstance()->score2 == true)//5.25 
	{
		space2 = true;
	}
	return true;
}

void Item::onDataInit()
{
	hpuse = false;
	scrolluse = false;
	scoreuse = false;//5.19
	dustuse = false;//5.25
	randombox = false;//5.25
	randombox2 = false;//5.25
	random = false;//5.25
	space = false;//5.25
	space2 = false;//5.25
	rect = false;
	rect2 = false;
}

bool Item::onTouchBegan(Touch *touch, Event *unused_event)
{
	Point location = touch->getLocation();

	auto spr_1 = (Sprite*)this->getChildByTag(150);
	Rect rect_1 = spr_1->getBoundingBox();
	auto spr_2 = (Sprite*)this->getChildByTag(250);
	Rect rect_2 = spr_2->getBoundingBox();

	if (rect_1.containsPoint(location))//첫번쨰칸
	{
		if (dataSingleton::getInstance()->life == true)
		{
			hpuse = true;
			rect = true;
			dataSingleton::getInstance()->life = false;

		}

		if (dataSingleton::getInstance()->scroll == true)
		{
			scrolluse = true;
			rect = true;
			dataSingleton::getInstance()->scroll = false;
			dataSingleton::getInstance()->scrolldown = true;//5.19

		}

		if (dataSingleton::getInstance()->score == true)//5.19
		{
			scoreuse = true;
			rect = true;
			dataSingleton::getInstance()->score = false;
			dataSingleton::getInstance()->scoreup = true;

		}

		if (dataSingleton::getInstance()->dust == true)
		{
			dustuse = true;
			rect = true;
		}

		if (dataSingleton::getInstance()->speed == true)//5.30
		{
			dataSingleton::getInstance()->speeddown = true;
			rect = true;
		}

		if (randombox == true)//5.25 랜덤박스를 클릭하면 랜덤으로돌림
		{
			random = true;
			rect = true;
			space = false;
			randombox = false;
			ran = rand() % 5 + 1;//5.30

		}
	}


	if (rect_2.containsPoint(location))//두번쨰칸
	{

		if (dataSingleton::getInstance()->life2 == true)
		{
			hpuse = true;
			rect2 = true;

		}

		if (dataSingleton::getInstance()->scroll2 == true)
		{
			scrolluse = true;
			rect2 = true;
			dataSingleton::getInstance()->scroll2 = false;
			dataSingleton::getInstance()->scrolldown = true;//5.19

		}

		if (dataSingleton::getInstance()->score2 == true)//5.19
		{
			scoreuse = true;
			rect2 = true;
			dataSingleton::getInstance()->score2 = false;
			dataSingleton::getInstance()->scoreup = true;

		}
		if (dataSingleton::getInstance()->dust == true)//5.25
		{
			dustuse = true;
			rect2 = true;
		}

		if (dataSingleton::getInstance()->speed == true)//5.30
		{
			dataSingleton::getInstance()->speeddown = true;
			rect2 = true;
		}

		if (randombox2 == true)//5.25 랜덤박스를 클릭하면 랜덤으로돌림
		{
			random = true;
			rect2 = true;
			space2 = false;
			randombox2 = false;
			ran = rand() % 5 + 1;//5.30

		}

	}

	return true;
}

void Item::onUpdate(float delta)
{
	////첫번째칸////
	if (hpuse == true && rect == true)
	{
		this->removeChild(spr_life);//5.30
		space = false;//5.25

	}

	if (scrolluse == true && rect == true)
	{
		this->removeChild(spr_scroll);//5.30
		space = false;//5.25

	}

	if (scoreuse == true && rect == true)//5.19
	{
		this->removeChild(spr_score);//5.30
		space = false;//5.25

	}
	if (dustuse == true && rect == true)
	{
		this->removeChild(spr_dust);
		space = false;
	}

	if (dataSingleton::getInstance()->speeddown == true && rect == true)
	{
		this->removeChild(spr_speed);//5.30
		space = false;
	}

	////두번째칸////
	if (hpuse == true && rect2 == true)
	{
		this->removeChild(spr_life2);//5.30
		space2 = false;//5.25

	}

	if (scrolluse == true && rect2 == true)
	{
		this->removeChild(spr_scroll2);//5.30
		space2 = false;//5.25

	}

	if (scoreuse == true && rect2 == true)//5.19
	{
		this->removeChild(spr_score2);//5.30
		space2 = false;//5.25

	}

	if (dustuse == true && rect2 == true)
	{
		this->removeChild(spr_dust2);//5.30
		space2 = false;
	}

	if (dataSingleton::getInstance()->speeddown == true && rect2 == true)
	{
		this->removeChild(spr_speed2);//5.30
		space2 = false;
	}

	/////랜덤박스///////  //5.25
	if (space == false && dataSingleton::getInstance()->stagechange == true)
	{
		spr_ranbox = Sprite::create("box.png");
		spr_ranbox->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));


		this->addChild(spr_ranbox, 20);

		rect = false;
		randombox = true;
		space = true;
		dataSingleton::getInstance()->stagechange = false;

	}

	if (space2 == false && dataSingleton::getInstance()->stagechange == true)
	{
		spr_ranbox2 = Sprite::create("box.png");
		spr_ranbox2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));


		this->addChild(spr_ranbox2, 20);

		rect2 = false;
		randombox2 = true;
		space2 = true;
		dataSingleton::getInstance()->stagechange = false;

	}
/////////////랜덤 돌리는부분///////////////


	/////첫번째칸/////////////
	if (random == true && rect == true)
	{
		spr_ranbox->setVisible(false);

		if (ran == 1)// 라이프
		{
			spr_life = Sprite::create("lifeup.png");
			spr_life->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_life, 20);

			dataSingleton::getInstance()->life = true;
			rect = false;
			space = true;
			random = false;
			hpuse = true;

		}

		if (ran == 2)// 스크롤
		{
			spr_scroll = Sprite::create("scroll.png");
			spr_scroll->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_scroll, 20);

			dataSingleton::getInstance()->scroll = true;
			rect = false;
			space = true;
			random = false;
			scrolluse = true;
		}

		if (ran == 3)//스코어
		{
			spr_score = Sprite::create("score.png");
			spr_score->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_score, 20);

			dataSingleton::getInstance()->score = true;
			rect = false;
			space = true;
			random = false;
			scoreuse = true;
		}

		if (ran == 4)//더스트
		{
			spr_dust = Sprite::create("dust.png");
			spr_dust->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_dust, 20);

			dataSingleton::getInstance()->dust = true;
			rect = false;
			space = true;
			random = false;


		}

		if (ran == 5)//스피드 5.30
		{
			spr_speed = Sprite::create("speed.png");
			spr_speed->setPosition(Point(mOrigin.x + mVisibleSize.width / 13, mOrigin.y + mVisibleSize.height - 30));

			this->addChild(spr_speed, 20);

			dataSingleton::getInstance()->speed = true;
			rect = false;
			space = true;
			random = false;
		}
	}
		
	///////////////두번째칸//////////////
	if (random == true && rect2 == true)
	{
		spr_ranbox2->setVisible(false);

		if (ran == 1)// 라이프
		{
			spr_life2 = Sprite::create("lifeup.png");
			spr_life2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_life2, 20);

			dataSingleton::getInstance()->life2 = true;
			rect2 = false;
			space2 = true;
			random = false;
			hpuse = true;

		}

		if (ran == 2)// 스크롤
		{
			spr_scroll2 = Sprite::create("scroll.png");
			spr_scroll2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_scroll2, 20);

			dataSingleton::getInstance()->scroll2 = true;
			rect2 = false;
			space2 = true;
			random = false;
			scrolluse = true;
		}

		if (ran == 3)//스코어
		{
			spr_score2 = Sprite::create("score.png");
			spr_score2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_score2, 20);

			dataSingleton::getInstance()->score2 = true;
			rect2 = false;
			space2 = true;
			random = false;
			scoreuse = true;
		}

		if (ran == 4)//더스트
		{
			spr_dust2 = Sprite::create("dust.png");
			spr_dust2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_dust2, 20);

			dataSingleton::getInstance()->dust = true;
			rect2 = false;
			space2 = true;
			random = false;
		}

		if (ran == 5)//스피드 5.30
		{
			spr_speed2 = Sprite::create("speed.png");
			spr_speed2->setPosition(Point(mOrigin.x + mVisibleSize.width / 4.5, mOrigin.y + mVisibleSize.height - 30));


			this->addChild(spr_speed2, 20);

			dataSingleton::getInstance()->speed2 = true;
			rect = false;
			space = true;
			random = false;
		}

	}
	setDust();
}

void Item::setDust()
{
	if (dataSingleton::getInstance()->dust == true && dustuse == true)//5.25
	{
		spr = Sprite::create("dust01.png");
		spr->setPosition(Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2));
		spr->setZOrder(100);
		this->addChild(spr);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.3);

		animation->addSpriteFrameWithFile("dust01.png");
		animation->addSpriteFrameWithFile("dust02.png");
		animation->addSpriteFrameWithFile("dust03.png");

		auto action = Sequence::create(
			Animate::create(animation),
			MoveTo::create(0.7, Point(mOrigin.x + mVisibleSize.width - mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2)),
			CallFuncN::create(CC_CALLBACK_1
			(Item::resetDust, this)), NULL);
		spr->runAction(action);
	}
}
void Item::resetDust(Ref *sender)
{
	auto spr = (Sprite*)sender;
	
	this->removeChild(spr);
	dataSingleton::getInstance()->dust = false;
	dustuse = false;
}