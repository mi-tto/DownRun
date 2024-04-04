#include "Character.h"
#include "GameScene.h"
#include "StageIdx.h"
#include "SimpleAudioEngine.h"//5.19
#include "B_Singleton.h"//5.30

using namespace CocosDenshion;//5.19

bool Character::init()
{
	if (!Layer::init())
	{
		return false;
	}

	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();

	onLoadSprites();
	onInit();

	return true;
}

// 스프라이트 init
void Character::onLoadSprites()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("playerplist.plist");
	auto sprRun = Sprite::createWithSpriteFrameName("player_01.png");

	sprRun->setAnchorPoint(Point::ZERO);
	sprRun->setPosition(m_x, m_y);
	sprRun->setTag(TAG_SPRITE_PLAYER_RUN);
	this->addChild(sprRun, 1);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3);

	for (int i = 0; i < 10; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("player_%02d.png", i + 1));
		animation->addSpriteFrame(frame);
	}

	auto animate = Animate::create(animation);
	sprRun->runAction(RepeatForever::create(animate));

	auto sprJump = Sprite::create("jump.png");
	m_x = mOrigin.x + mVisibleSize.width / 2;
	m_y = (mOrigin.y + mVisibleSize.height) + sprJump->getContentSize().height;
	sprJump->setAnchorPoint(Point::ZERO);
	sprJump->setPosition(m_x, m_y);
	sprJump->setTag(TAG_SPRITE_PLAYER_JUMP);
	sprJump->setVisible(false);
	this->addChild(sprJump, 1);
}


// 기본 자료형 변수 초기화
void Character::onInit()
{
	m_hp = mMaxHp;

	jumpTick = 0;
	isJump = false;

	misCollision = false;
	misTouch = false;
	mTouchDir = PLAYER_DIR::NONE;
	mState = 3;

	misObstacleCollision = false;

	isFlip = false;

	auto sprPlayer = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER_RUN);

	auto listner = EventListenerTouchOneByOne::create();
	listner->onTouchBegan = CC_CALLBACK_2(Character::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listner, 1);
}

void Character::onRelease()
{

}

bool Character::onTouchBegan(Touch* touch, Event* unused_event)
{
	misTouch = true;

	if (touch->getLocation().x >= mVisibleSize.width / 2)
		mTouchDir = PLAYER_DIR::RIGHT;
	else
		mTouchDir = PLAYER_DIR::LEFT;

	return true;
}

void Character::onTouchEnded(Touch* touch, Event* unused_event)
{
	misTouch = false;
}

// 떨어질 때 x, y축 이동
void Character::onFallingMyPosition(float delta)
{
	auto preSpr = (Sprite*)this->getChildByTag(mState);
	preSpr->setVisible(false);

	auto sprPlayer = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER_JUMP);
	sprPlayer->setVisible(true);
	mState = 3;


	// 화면 벽 넘지 못하게
	float max_X = mVisibleSize.width - sprPlayer->getContentSize().width; // setAnchorPoint(Point::ZERO)

	if (m_x <= 0)
	{
		m_x = 0;

		if (mTouchDir == PLAYER_DIR::RIGHT)
		{
			m_x += delta*mPlayer_X_MoveSpeed;
		}
	}
	else if (m_x >= max_X)
	{
		m_x = max_X;

		if (mTouchDir == PLAYER_DIR::LEFT)
		{
			m_x -= delta*mPlayer_X_MoveSpeed;
		}
	}
	else
	{
		// 캐릭터의 방향에 따라 이미지 변경
		switch (mTouchDir)
		{
		case PLAYER_DIR::NONE:
		{
					 m_y -= delta*mPlayer_Y_Speed * 4;
					 sprPlayer->setPositionY(m_y);
					 return;
		}
			break;
		case PLAYER_DIR::LEFT:
		{
					 auto _flipx = FlipX::create(false);
					 sprPlayer->runAction(_flipx);
					 m_x -= delta*mPlayer_X_MoveSpeed;
		}
			break;
		case PLAYER_DIR::RIGHT:
		{
					  auto _flipx = FlipX::create(true);
					  sprPlayer->runAction(_flipx);
					  m_x += delta*mPlayer_X_MoveSpeed;
		}
			break;
		default:
			break;
		}
	}

	m_y -= delta*mPlayer_Y_Speed;
	sprPlayer->setPosition(Point(m_x, m_y));
}

// 블럭 위에 있을 경우 x축 이동
void Character::onMoveXPosition(float delta)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER_RUN);

	// 게임 시작 시 블럭에 닿을 때, 왼쪽이동 고정
	if (mState == 3 && mTouchDir == PLAYER_DIR::NONE)
	{
		misTouch = true;
		mTouchDir = PLAYER_DIR::LEFT;
	}

	if (misTouch)
	{
		// 캐릭터의 방향에 따라 이미지 변경
		switch (mTouchDir)
		{
		case PLAYER_DIR::NONE:
			break;
		case PLAYER_DIR::LEFT:
		{
					 auto _flipx = FlipX::create(false);
					 sprPlayer->runAction(_flipx);
					 m_x -= delta*mPlayer_X_Speed;
		}
			break;
		case PLAYER_DIR::RIGHT:
		{
					  auto _flipx = FlipX::create(true);
					  sprPlayer->runAction(_flipx);
					  m_x += delta*mPlayer_X_Speed;
		}
			break;
		default:
			break;
		}

		sprPlayer->setPositionX(m_x);
	}

	mState = 2;
}

// 라이프 0개일 시 죽는 모션 함수
void Character::onDieMove()
{
	auto preSpr = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER_RUN);
	preSpr->setVisible(false);

	preSpr = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER_JUMP);
	preSpr->setVisible(false);


	auto dieSpr = Sprite::create("player_08.png"); // 이미지 1개로 고정
	dieSpr->setAnchorPoint(Point::ZERO);
	dieSpr->setPosition(m_x, m_y);
	this->addChild(dieSpr);

	int soundID_0 = SimpleAudioEngine::getInstance()->
		playEffect("die.mp3");//5.19

	switch (mTouchDir)
	{
	case PLAYER_DIR::LEFT:
	{
					auto _flipx = FlipX::create(false);
					dieSpr->runAction(_flipx);
					
					auto action_0 = MoveBy::create(1.0, Point(0, 100));
					auto action_1 = MoveTo::create(2.0, Point(0, -dieSpr->getContentSize().width));
					auto action_2 = Sequence::create(action_0, action_1, NULL);
					dieSpr->runAction(action_2);
	}
		break;
	case PLAYER_DIR::RIGHT:
	{
					auto _flipx = FlipX::create(true);
					dieSpr->runAction(_flipx);

					auto action_0 = MoveBy::create(1.0, Point(0, 50));
					auto action_1 = MoveTo::create(2.0, Point(0, -dieSpr->getContentSize().width));
					auto action_2 = Sequence::create(action_0, action_1, NULL);
					dieSpr->runAction(action_2);
	}
		break;
	default:
		break;
	}
}

// 장애물에 닿았을 경우 튕겨나가는 함수
void Character::onJump(float delta, float blockspeed)
{
	auto preSpr = (Sprite*)this->getChildByTag(mState);
	preSpr->setVisible(false);

	auto sprPlayer = (Sprite*)this->getChildByTag(TAG_SPRITE_PLAYER_JUMP);
	sprPlayer->setVisible(true);

	int soundID_1 = SimpleAudioEngine::getInstance()->
		playEffect("pain.wav");//5.19

	jumpTick += delta;

	if (jumpTick >= 0.25f)
	{
		switch (mJumpDir)
		{
		case PLAYER_DIR::LEFT:
		{
					 m_x += delta * 100;
		}
			break;
		case PLAYER_DIR::RIGHT:
		{
					  m_x -= delta * 100;
		}
			break;
		}

		m_y -= delta*blockspeed;
		sprPlayer->setPosition(m_x, m_y);

		if (jumpTick >= 0.5f)
		{
			isJump = false;
			jumpTick = 0;
			mJumpDir = PLAYER_DIR::NONE;
			misObstacleCollision = false;
		}
	}
	else
	{
		switch (mJumpDir)
		{
		case PLAYER_DIR::LEFT:
		{
					 m_x += delta * 100;
		}
			break;
		case PLAYER_DIR::RIGHT:
		{
					  m_x -= delta * 100;
		}
			break;
		}

		m_y += delta*blockspeed*2;
		sprPlayer->setPosition(m_x, m_y);
	}
}

void Character::onUpdate(float delta, Block** block, int sNum, int maxNum)
{
	auto sprPlayer = (Sprite*)this->getChildByTag(mState);

	// 스테이지 2 일 경우, 펀치랑 충돌 체크 // 05.26
	GameScene* g = GameScene::Get_Instance();
	StageIdx* sidx = g->GetStageLayer();

	int sIdxNum = sidx->Get_Stage_idx();

	// 스테이지 2 일 경우, 벽면충돌체 충돌체크
	if (sIdxNum == 2)
	{
		Rect myRect = sprPlayer->getBoundingBox();
		Rect punch = sidx->Get_PunchRect();

		if (!misObstacleCollision && myRect.intersectsRect(punch))
		{
			m_hp--;
			mJumpDir = mTouchDir;
			isJump = true;
			misObstacleCollision = true;
			IsDamaged = true;
		}

		if (isJump)
		{
			onJump(delta, block[0]->Get_blockSpeed());
			m_y += delta*block[0]->Get_blockSpeed();
			sprPlayer->setPositionY(m_y);
			return;
		}
	}

	// 장애물이 있는 경우 충돌체크
	for (int i = sNum; i < maxNum; i++)
	{
		if (block[i]->mGet_obstacle())
		{
			Rect myRect = sprPlayer->getBoundingBox();
			Rect obBox = block[i]->onGet_ObSprBoundingBox();

			if (myRect.intersectsRect(obBox) && !isJump)
			{
				m_hp--;
				mJumpDir = mTouchDir;
				isJump = true;
				misObstacleCollision = true;
				IsDamaged = true;
			}
		}
	}


	// 발판 위에있는 경우
	if (misCollision)
	{
		Block* _block = block[mCollisionIdx];
		Rect myRect = Rect(m_x,
							m_y,
			sprPlayer->getContentSize().width,
			sprPlayer->getContentSize().height / 5);


		bool isConv = _block->onGet_isConvey();


		// 컨베이어 위에있는 경우
		if (isConv)
		{
			int _dir = _block->onGet_Dir();

			switch (_dir)
			{
			case CONVEYOR_DIR::D_LEFT:
				{
									   m_x -= delta * 100;
				}
				break;
			case CONVEYOR_DIR::D_RIGHT:
				{
										m_x += delta * 100;
				}
				break;
			}

			sprPlayer->setPositionX(m_x);
		}

		if (isJump)
		{
			onJump(delta, _block->Get_blockSpeed()); // 점프 ㄱㄱ
			m_y += delta*_block->Get_blockSpeed();
			sprPlayer->setPositionY(m_y);
			return;
		}
		
		// 블럭을 밟았을 경우 -> x축 이동
		if (!myRect.intersectsRect(_block->onGet_CollisionRect()))
		{
			misCollision = false;
			return;
		}
		else // 아닌 경우 -> 하강
		{
			onMoveXPosition(delta);
			m_y += delta*_block->Get_blockSpeed();

			sprPlayer->setVisible(false);

			auto spr = (Sprite*)this->getChildByTag(mState);
			spr->setVisible(true);

			spr->setPositionY(m_y);

			return;
		}
	}


	for (int i = sNum; i < maxNum; i++)
	{
		int num = block[i]->mGetObstableNumber();

		// 장애물이 낙하체일 경우
		if (num == TAG_SPRITE_TRAP)
		{
			Rect myRect = sprPlayer->getBoundingBox();
			Rect c_rect = block[i]->getCollisionRect(); // 3등분 렉트

			if (myRect.intersectsRect(c_rect) &&
				m_y + 100 < block[i]->onGetObstableYpos())
			{
				block[i]->onSetFalling(true);
			}
		}

		// 발판 위가 아닌 경우
		if (!misCollision)
		{
			Rect myRect = Rect(m_x, m_y,
				sprPlayer->getContentSize().width, sprPlayer->getContentSize().height / 3);

			if (block[i]->onGetSpr()->isVisible())
			{
				// 블럭의 rect를 받아옴
				if (!myRect.intersectsRect(block[i]->onGet_CollisionRect()))
				{
					onFallingMyPosition(delta);
				}
				else
				{
					misCollision = true;
					mCollisionIdx = i;
					return;
				}
			}
		}
	}

	if (dataSingleton::getInstance()->speeddown == true)//5.30
	{
		mPlayer_X_Speed = 100;
		this->schedule(schedule_selector
			(Character::resetSpeed), 10.0);
	}

	if (dataSingleton::getInstance()->speeddown == false)//5.30
	{
		mPlayer_X_Speed = 200;
	}
}

void Character::resetSpeed(float delta)//5.30
{
	dataSingleton::getInstance()->speeddown = false;

}