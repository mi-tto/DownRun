#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Item.h"

USING_NS_CC;

enum CONVEYOR_DIR
{
	D_NONE,
	D_LEFT,
	D_RIGHT
};

enum BLOCK_TYPE
{
	TWO = 0, 
	THREE, 
	FOUR 
};

#define TAG_SPRITE_TWO				0
#define TAG_SPRITE_THREE			1
#define TAG_SPRITE_FOUR				2

#define TAG_OBSTACLE_THORN			3000
#define TAG_SPRITE_TRAP				4000
#define TAG_OBSTACLE_CONTEINER		5000

class Block : public cocos2d::Layer
{
private:

	Size mVisibleSize;
	Vec2 mOrigin;

	CONVEYOR_DIR block_dir; // 컨베이어 블럭 방향
	BLOCK_TYPE blockType; // 블럭 종류

	Sprite* pObstacleSpr; // 장애물 spr

	Item* mItem;

	///////////////////////////////////

	Rect visibleRect[3];
	Rect mCheckCollisionRect;
	const int maxVisibleRect = 3;

	/////////////////////////////////////

	float m_x;
	float m_y;

	float mSpeed;
	bool isObstacle;
	bool falling;

	bool isConvey;

	void onInit();

public:
	virtual ~Block();

	virtual bool init();

	void onDataInit(int blocknum, int _height); // 초기화
	void onUpdate(float deltaTime, Block* preBlock);
	void onMakeConvey(); // 컨베이어 블럭 생성 함수

	int onGet_Dir()
	{
		return block_dir;
	}

	float onGetObstableYpos()
	{
		if (pObstacleSpr != NULL && isObstacle)
		{
			float _y = pObstacleSpr->getPositionY();
			return _y;
		}
		return NULL;
	}

	float Get_blockSpeed()
	{
		return mSpeed;
	}

	Sprite* onGetSpr()
	{
		if (isConvey)
		{
			auto spr = (Sprite*)this->getChildByTag(TAG_OBSTACLE_CONTEINER);
			return spr;
		}
		else
		{
			auto spr = (Sprite*)this->getChildByTag(blockType);
			return spr;
		}
	}

	float mGet_mY()
	{
		if (isConvey)
		{
			auto spr = (Sprite*)this->getChildByTag(TAG_OBSTACLE_CONTEINER);
			return spr->getPositionY();
		}
		else
		{
			auto spr = (Sprite*)this->getChildByTag(blockType);
			return spr->getPositionY();
		}
	}

	bool mGet_obstacle()
	{
		return isObstacle;
	}

	int mGetObstableNumber()
	{
		if (pObstacleSpr != NULL && isObstacle && !isConvey)
			return pObstacleSpr->getTag();

		return NULL;
	}

	Rect getCollisionRect()
	{
		return mCheckCollisionRect;
	}

	Rect onGet_ObSprBoundingBox()
	{
		if (pObstacleSpr != NULL && isObstacle && !isConvey)
			return pObstacleSpr->getBoundingBox();

		return Rect::ZERO;
	}

	Rect onGet_CollisionRect()
	{
		if (isConvey)
		{
			auto spr = (Sprite*)this->getChildByTag(TAG_OBSTACLE_CONTEINER);
			Rect rect = spr->getBoundingBox();
			return rect;
		}
		else
		{
			auto spr = (Sprite*)this->getChildByTag(blockType);
			Rect rect = Rect(m_x,
				m_y - (spr->getContentSize().height / 6),
				spr->getContentSize().width,
				spr->getContentSize().height / 6);
			return rect;
		}
	}

	void onSetFalling(bool t)
	{
		falling = t;
	}

	bool onGetFalling()
	{
		return falling;
	}

	bool onGet_isConvey()
	{
		return isConvey;
	}

	CREATE_FUNC(Block);

	// 아이템 먹으면 블럭이 느려짐
	void resetScroll(float delta);//5.19
};

#endif // __HELLOWORLD_SCENE_H__