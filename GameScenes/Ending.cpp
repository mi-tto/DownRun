#include"Ending.h"
#include "Intro.h"
#include"GameScene.h"

Scene* Ending::CreateScene()
{
	// auto�� Scene* �� ����.
	auto scene = Scene::create();

	// ������� �����ص� CREATE_FUNC(HelloWorld)���� HelloWorld::create() ����� ������ ����
	auto layer = Ending::create();

	// scene->addchile(layer, 0, -1) �� ����. ���� zOrder�� tag�� �⺻���̴�.
	scene->addChild(layer);

	return scene;
}

bool Ending::init()
{
	if (!Layer::init())
	{
		return false;
	}

	DrawEnd();
}

void Ending::DrawEnd()
{
	auto Pause_Home = Sprite::create("end_home.png");
	auto item_1 = MenuItemSprite::create(Pause_Home, NULL, CC_CALLBACK_1(Ending::GameGoHome, this));
	auto Pause_Replay = Sprite::create("end_replay.png");
	auto item_2 = MenuItemSprite::create(Pause_Replay, NULL, CC_CALLBACK_1(Ending::GameReplay, this));

	auto menu = Menu::create(item_1, item_2, NULL);

	item_1->setPosition(Point(mOrigin.x / 2 - mVisibleSize.width / 6, mOrigin.y / 2 - mVisibleSize.height / 3));
	item_1->setScale(0.7f);
	item_2->setPosition(Point(mOrigin.x / 2 + mVisibleSize.width / 6, mOrigin.y / 2 - mVisibleSize.height / 3));
	item_2->setScale(0.7f);

	this->addChild(menu, 3);
}


void Ending::GameReplay(Ref *Sender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(GameScene::createScene());
	CCDirector::sharedDirector()->resume();
}

void Ending::GameGoHome(Ref *Sender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(Intro::createScene());
	CCDirector::sharedDirector()->resume();
}


