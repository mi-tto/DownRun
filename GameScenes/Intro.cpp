#include "Intro.h"
#include "Store.h"
#include "SimpleAudioEngine.h"//5.19

using namespace CocosDenshion;//5.19

Scene* Intro::createScene()
{
	// auto는 Scene* 과 동일.
	auto scene = Scene::create();

	// 헤더에서 선언해둔 CREATE_FUNC(HelloWorld)으로 HelloWorld::create() 방식의 선언이 가능
	auto layer = Intro::create();

	// scene->addchile(layer, 0, -1) 과 동일. 각각 zOrder와 tag의 기본값이다.
	scene->addChild(layer);

	return scene;
}

bool Intro::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Intro::onTouch, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);

	SimpleAudioEngine::getInstance()->
		playBackgroundMusic("bgm_02.mp3");//5.19

	onLoad();

	return true;
}

void Intro::onInit()
{

}

void Intro::onLoad()
{
	/*인트로 화면 메뉴 출력*/
	auto Spr = Sprite::create("intro.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2));
	this->addChild(Spr, 1);

	Spr = Sprite::create("logo.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2 + 155));
	this->addChild(Spr, 2);

	Spr = Sprite::create("start.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2 + 100 - 60));
	Spr->setScale(0.6f);
	Spr->setOpacity(180);
	this->addChild(Spr, 2, TAG_START);

	Spr = Sprite::create("store.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2 - 60)); //중간
	Spr->setScale(0.6f);
	Spr->setOpacity(180);
	this->addChild(Spr, 2, TAG_ITEM);

	Spr = Sprite::create("exit.png");
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2 - 100 - 60));
	Spr->setScale(0.6f);
	Spr->setOpacity(180);
	this->addChild(Spr, 2, TAG_EXIT);
}

void Intro::onRelease()
{

}

bool Intro::onTouch(Touch *touch, Event * event)
{
	Point location = touch->getLocation();

	auto Spr = (Sprite*)this->getChildByTag(TAG_START);
	Rect START = Spr->getBoundingBox();
	Spr = (Sprite*)this->getChildByTag(TAG_ITEM);
	Rect ITEM = Spr->getBoundingBox();
	Spr = (Sprite*)this->getChildByTag(TAG_EXIT);
	Rect EXIT = Spr->getBoundingBox();

	if (START.containsPoint(location))
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		Director::getInstance()->replaceScene(GameScene::createScene());
		//init에서 처음 등록하는 eventListener는 등록한 레이어가 소멸되어도 해제되지않아서 직접 없애주어야함.
		//없애주지 않으면 씬을 생성하고 없애는 과정에서 터치 이벤트가 일어나면 그대로 프로그램이 죽어버림.
	}
	else if (ITEM.containsPoint(location))
	{
		Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
		auto scene = TransitionFade::create(0.7,
			Store::createScene());
		Director::getInstance()->replaceScene(scene);//5.19
	}
	else if (EXIT.containsPoint(location))
	{
		exit(1);
	}

	return true;
}

void Intro::ChangeScnene()
{

}