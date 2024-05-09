#include "Block.h"
#include "GameScene.h"
#include "B_Singleton.h"//5.19

bool Block::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void Block::onInit()
{
	mVisibleSize = Director::getInstance()->getVisibleSize();
	mOrigin = Director::getInstance()->getVisibleOrigin();

	mSpeed = 300;
	isObstacle = false;
	falling = false;
	isConvey = false;

	/////////////////////////////////////////////

	mCheckCollisionRect = Rect::ZERO;

	float scoff = mVisibleSize.width / 3;
	float a = 0;

	for (int i = 0; i < maxVisibleRect; i++)
	{
		visibleRect[i] = Rect(a, 0, scoff, mVisibleSize.height);
		a += scoff;
	}

	///////////////////////////////////////////////////
}

void Block::onDataInit(int blocknum, int _height)
{
	onInit();

	Sprite* spr;
	int temp;

	mItem = Item::create();
	this->addChild(mItem);

	// 블럭 종류에 따라 spr 생성
	switch (blocknum)
	{
		case TWO:
		{
					spr = Sprite::create("block_2.png");
					blockType = TWO;
					temp = (int)spr->getContentSize().width / 2;
		}
			break;
		case THREE:
		{
					  spr = Sprite::create("block_3.png");
					  blockType = THREE;
					  temp = (int)spr->getContentSize().width / 3;
		}
			break;
		case FOUR:
		{
					 spr = Sprite::create("block_4.png");
					 blockType = FOUR;
					 temp = (int)spr->getContentSize().width / 4;
		}
			break;
	}

	spr->setTag(blockType);

	m_x = rand() % ((int)mVisibleSize.width - ((int)spr->getContentSize().width + temp) - ((int)mOrigin.x + temp)) + (mOrigin.x + temp);
	m_y = (mOrigin.y + mVisibleSize.height) - (spr->getContentSize().height * _height);

	// 처음 블럭 3개는 안보이도록
	if (_height == 1 || _height == 5 || _height == 9)
	{
		spr->setVisible(false);
	}

	spr->setAnchorPoint(Point(0, 1));
	spr->setPosition(Point(m_x, m_y));
	this->addChild(spr, 1);

}

void Block::onUpdate(float deltaTime, Block* preBlock)
{
	Sprite* spr;

	// 블럭 종류에 따라 스프라이트 받아옴
	if (isConvey)
	{
		spr = (Sprite*)this->getChildByTag(TAG_OBSTACLE_CONTEINER);
	}
	else
	{
		spr = (Sprite*)this->getChildByTag(blockType);
	}

	m_y += deltaTime*mSpeed;
	spr->setPositionY(m_y);

	bool scrolldown = mItem->onGet_ScrollUse();

	// 장애물이 잇으면 같이 y축 +
	if (isObstacle && !isConvey)
	{
		if (pObstacleSpr != NULL)
		{
			if (!falling)
			{
				float _y = pObstacleSpr->getPositionY();
				_y += deltaTime*mSpeed;
				pObstacleSpr->setPositionY(_y);
			}
			else
			{
				float _y = pObstacleSpr->getPositionY();
				_y += deltaTime*(-3)*mSpeed;

				if (_y <= 0)
				{
					auto _action = RemoveSelf::create();
					pObstacleSpr->runAction(_action);
					pObstacleSpr = NULL;
					isObstacle = false;
					falling = false;
				}
				else
					pObstacleSpr->setPositionY(_y);
			}
		}
	}

	// 이전 블럭에서 가졌던 장애물이 컨테이너가 되고, 낙하체가 떨어져야하는 경우
	if (isObstacle && isConvey && falling)
	{
		Sprite* spr;
		spr = (Sprite*)this->getChildByTag(TAG_SPRITE_TRAP);

		float _y = spr->getPositionY();
		_y += deltaTime*(-3)*mSpeed;

		if (_y <= 0)
		{
			auto _action = RemoveSelf::create();

			spr->runAction(_action);
			isObstacle = false;
			falling = false;
		}
		else
			spr->setPositionY(_y);
	}

	// 화면 넘어가면
	if (m_y >= mVisibleSize.height + spr->getContentSize().height)
	{
		// 블럭 삭제
		auto action = RemoveSelf::create();
		spr->runAction(action);

		if (!isConvey)
		{
			// 장애물 삭제
			if (isObstacle && pObstacleSpr != NULL)
			{
				if (pObstacleSpr->getTag() == TAG_OBSTACLE_TRAP)
				{
					if (!falling)
					{
						auto _action = RemoveSelf::create();
						pObstacleSpr->runAction(_action);
						isObstacle = false;
					}
				}
				else
				{
					auto _action = RemoveSelf::create();
					pObstacleSpr->runAction(_action);
					isObstacle = false;
					falling = false;
				}
				pObstacleSpr = NULL;
			}
		}

		if (isConvey)
			isConvey = false;

		// 블럭 다시 생성
		int random = rand() % 3;
		int temp;
		switch (random)
		{
			case TWO:
			{
						spr = Sprite::create("block_2.png");
						blockType = TWO;
						temp = (int)spr->getContentSize().width / 2;
			}
				break;
			case THREE:
			{
						  spr = Sprite::create("block_3.png");
						  blockType = THREE;
						  temp = (int)spr->getContentSize().width / 3;
			}
				break;
			case FOUR:
			{
						 spr = Sprite::create("block_4.png");
						 blockType = FOUR;
						 temp = (int)spr->getContentSize().width / 4;
			}
				break;
		}

		m_x = rand() % ((int)mVisibleSize.width - ((int)spr->getContentSize().width + temp) - ((int)mOrigin.x + temp)) + (mOrigin.x + temp);

		int ran = rand() % 3 + 3; // 3~5 로 수정
		m_y = preBlock->mGet_mY() - spr->getContentSize().height * ran;

		if (m_y >= 0)
		{
			while (m_y >= 0)
			{
				int ran = rand() % 1 + 5;
				m_y = preBlock->mGet_mY() - spr->getContentSize().height * ran;
			}
		}

		spr->setTag(blockType);
		spr->setAnchorPoint(Point(0, 1));
		spr->setPosition(Point(m_x, m_y));
		this->addChild(spr, 1);

		GameScene* g = GameScene::Get_Instance();
		StageIdx* sidx = g->GetStageLayer();

		// stage에 따라 장애물 생성
		Sprite* temp = sidx->onMakeObstacle(spr, blockType, &isObstacle, falling);

		if (isObstacle)
		{
			if (temp == NULL) // 컨베이어
			{
				onMakeConvey();
				pObstacleSpr = NULL;
			}
			else
			{
				pObstacleSpr = temp;
				this->addChild(pObstacleSpr, 10);
			}
		}
		else
		{
			pObstacleSpr = NULL;
		}

		if (pObstacleSpr != NULL && isObstacle)
		{
			if (pObstacleSpr->getTag() == TAG_SPRITE_TRAP)
			{
				for (int i = 0; i < maxVisibleRect; i++)
				{
					float _x = pObstacleSpr->getPosition().x;

					if (_x >= visibleRect[i].getMinX() &&
						_x <= visibleRect[i].getMaxX())
					{
						mCheckCollisionRect = visibleRect[i];
					}
				}
			}	
		}
		return;
	}

	if (dataSingleton::getInstance()->scrolldown == true)//5.19
	{
		mSpeed = 30;
		this->schedule(schedule_selector
			(Block::resetScroll), 5.0);//5초가 지나면 스크롤속도를 원래대로
	}

	if (dataSingleton::getInstance()->scrolldown == false)//5.19
	{
		mSpeed = 100;
	}
}

void Block::onMakeConvey() // 컨베이어 생성 함수
{

	isConvey = true;

	unsigned int _type;
	char* _dir;

	int _ran = rand() % 100;

	this->removeChildByTag(blockType);

	Sprite* spr;

	// 블럭 타입에 맞게
	switch (blockType)
	{
	case TWO:
	{
				// 방향에 맞게 스프라이트 생성

				_type = 2;

				// <<<<<< 
				if (_ran >= 99)
				{
					_dir = "left";
					block_dir = CONVEYOR_DIR::D_LEFT;
					SpriteFrameCache::getInstance()->addSpriteFramesWithFile("convey_left_2.plist");
					spr = Sprite::createWithSpriteFrameName("conveyor_2_left_01.png");
				}
				//  >>>>>> 
				else
				{
					_dir = "Right";
					SpriteFrameCache::getInstance()->addSpriteFramesWithFile("convey_Right_02.plist");
					spr = Sprite::createWithSpriteFrameName("Conveyor_2_Right_01.png");
				}
		}
		break;
	case THREE:
		{
				_type = 3;

				//  <<<<<<  
				if (_ran >= 99)
				{
					_dir = "left";
					block_dir = CONVEYOR_DIR::D_LEFT;
					SpriteFrameCache::getInstance()->addSpriteFramesWithFile("convey_left_3.plist");
					spr = Sprite::createWithSpriteFrameName("conveyor_3_left_01.png");
				}
				//  >>>>>>  
				else
				{
					_dir = "right";
					block_dir = CONVEYOR_DIR::D_RIGHT;
					SpriteFrameCache::getInstance()->addSpriteFramesWithFile("convey_right_3.plist");
					spr = Sprite::createWithSpriteFrameName("conveyor_3_right_01.png");
				}
		}
		break;
	case FOUR:
		{
				_type = 4;

				//  <<<<<<  
				if (_ran >= 99)
				{
					_dir = "left";
					block_dir = CONVEYOR_DIR::D_LEFT;
					SpriteFrameCache::getInstance()->addSpriteFramesWithFile("convey_left_4.plist");
					spr = Sprite::createWithSpriteFrameName("conveyor_4_left_01.png");
				}
				//  >>>>>>  
				else
				{
					_dir = "right";
					block_dir = CONVEYOR_DIR::D_RIGHT;
					SpriteFrameCache::getInstance()->addSpriteFramesWithFile("convey_right_4.plist");
					spr = Sprite::createWithSpriteFrameName("conveyor_4_right_01.png");
				}
		}
		break;
	}				

	spr->setAnchorPoint(Point(0, 1));
	spr->setPosition(Point(m_x, m_y));
	spr->setTag(TAG_OBSTACLE_CONTEINER);
	spr->setScale(0.8);
	this->addChild(spr);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.3);

	for (int i = 0; i < 13; i++)
	{
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("conveyor_%d_%s_%02d.png", _type, _dir, i + 1));
		animation->addSpriteFrame(frame);
	}

	auto animate = Animate::create(animation);
	spr->runAction(RepeatForever::create(animate));
}

Block::~Block()
{
	
}

void Block::resetScroll(float delta)//5.19
{
	dataSingleton::getInstance()->scrolldown = false;

}