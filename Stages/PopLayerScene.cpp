#include "PopLayerScene.h"
#include "GameScene.h"
#include "intro.h"

using namespace cocos2d;

Scene* PopLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = PopLayer::create();
	scene->addChild(layer);
	return scene;
}


bool PopLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}


	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();

	auto Pause_Continue = Sprite::create("pause_continue.png");
	auto item_1 = MenuItemSprite::create(Pause_Continue, NULL, CC_CALLBACK_1(PopLayer::GameContinue, this));
	auto Pause_Home = Sprite::create("pause_home.png");
	auto item_2 = MenuItemSprite::create(Pause_Home, NULL, CC_CALLBACK_1(PopLayer::GameGoHome, this));
	auto Pause_Replay = Sprite::create("pause_replay.png");
	auto item_3 = MenuItemSprite::create(Pause_Replay, NULL, CC_CALLBACK_1(PopLayer::GameReplay, this));
	auto menu = Menu::create(item_1, item_2, item_3,NULL);
	item_1->setPosition(Point(mOrigin.x / 2 - mVisibleSize.width / 6, mOrigin.y / 2 + mVisibleSize.height / 8));
	item_1->setScale(0.7f);
	item_2->setPosition(Point(mOrigin.x/2, mOrigin.y/2 - mVisibleSize.height / 8));
	item_2->setScale(0.7f);
	item_3->setPosition(Point(mOrigin.x / 2 + mVisibleSize.width / 6 , mOrigin.y / 2  + mVisibleSize.height / 8));
	item_3->setScale(0.7f);
	
	this->addChild(menu, 3);

	auto H_Pause = Sprite::create("h_pause.png");
	H_Pause->setPosition(Point(mOrigin.x + mVisibleSize.width / 2, mOrigin.y + mVisibleSize.height / 2));
	H_Pause->setScale(0.45f);
	H_Pause->setOpacity(180);
	this->addChild(H_Pause, 0);

	return true;
}

void PopLayer::GameContinue(Ref *Sender)
{
	this->removeAllChildren();
	CCDirector::sharedDirector()->resume();
	
}

void PopLayer::GameReplay(Ref *Sender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(GameScene::createScene());
	CCDirector::sharedDirector()->resume();
}


void PopLayer::GameGoHome(Ref *Sender)
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	Director::getInstance()->replaceScene(Intro::createScene());
	CCDirector::sharedDirector()->resume();
}


