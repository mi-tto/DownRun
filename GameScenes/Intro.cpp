#include "Intro.h"
#include "Store.h"
#include "SimpleAudioEngine.h"//5.19

using namespace CocosDenshion;//5.19

Scene* Intro::createScene()
{
	// auto�� Scene* �� ����.
	auto scene = Scene::create();

	// ������� �����ص� CREATE_FUNC(HelloWorld)���� HelloWorld::create() ����� ������ ����
	auto layer = Intro::create();

	// scene->addchile(layer, 0, -1) �� ����. ���� zOrder�� tag�� �⺻���̴�.
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
	/*��Ʈ�� ȭ�� �޴� ���*/
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
	Spr->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2 - 60)); //�߰�
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
		//init���� ó�� ����ϴ� eventListener�� ����� ���̾ �Ҹ�Ǿ ���������ʾƼ� ���� �����־����.
		//�������� ������ ���� �����ϰ� ���ִ� �������� ��ġ �̺�Ʈ�� �Ͼ�� �״�� ���α׷��� �׾����.
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