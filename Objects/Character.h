#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

#define TAG_SPRITE_PLAYER_RUN		2
#define TAG_SPRITE_PLAYER_JUMP		3

// 캐릭터 이동방향
enum PLAYER_DIR
{
	NONE,
	LEFT,
	RIGHT
};

class Character : public cocos2d::Layer
{
private:

	float mPlayer_X_Speed = 200; 
	const float mPlayer_X_MoveSpeed = 70; // 블럭 위 x축 스피드 
	const float mPlayer_Y_Speed = 40; // 떨어지는 속도
	const int mMaxHp = 3; // hp max

	Size mVisibleSize;
	Vec2 mOrigin;

	float m_x;
	float m_y;
	int m_hp; // 현재 hp

	int mState;

	float jumpTick;
	bool isJump;
	const float jumpYpos = 2; // 점프 y축 속도
	PLAYER_DIR mJumpDir; // 점프 시 스프라이트 방향

	int mCollisionIdx;
	bool misCollision;
	bool misObstacleCollision;
	bool misTouch;
	bool isFlip;
	PLAYER_DIR mTouchDir; // 터치 방향

	void onInit(); // 기본 변수 초기화
	void onLoadSprites(); // 스프라이트 초기화

	bool IsDamaged = false;

public:

	virtual bool init();

	CREATE_FUNC(Character);

	void onRelease();
	
	void onUpdate(float delta, Block** block, int sNum, int maxNum);
	void onFallingMyPosition(float delta); // y축 하강 처리
	void onMoveXPosition(float delta); // 벽돌 위 x축 이동 처리

	void onJump(float delta, float blockspeed); // 점프 처리
	void onDieMove(); // 라이프 0개일 시 죽는 모션 함수

	int onGetHp()
	{
		return m_hp;
	}

	void AddHp()
	{
		m_hp++;
	}

	int onGetMaxHp()
	{
		return mMaxHp;
	}

	bool GetIsDamaged()
	{
		return IsDamaged;
	}
	void SetIsDamaged(bool da)
	{
		IsDamaged = da;
	}

	Point Get_MyPosition()
	{
		Point pos;
		pos.x = m_x;
		pos.y = m_y;
		return pos;
	}

	float onGetypos()
	{
		return m_y;
	}

	void SetHp(int x)
	{
		m_hp = x;
	}

	bool onTouchBegan(Touch* touch, Event* unused_event);
	void onTouchEnded(Touch* touch, Event* unused_event);
	
	void resetSpeed(float delta);//5.30
};

#endif // __HELLOWORLD_SCENE_H__