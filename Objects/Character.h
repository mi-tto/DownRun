#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "Block.h"

USING_NS_CC;

#define TAG_SPRITE_PLAYER_RUN		2
#define TAG_SPRITE_PLAYER_JUMP		3

// ĳ���� �̵�����
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
	const float mPlayer_X_MoveSpeed = 70; // �� �� x�� ���ǵ� 
	const float mPlayer_Y_Speed = 40; // �������� �ӵ�
	const int mMaxHp = 3; // hp max

	Size mVisibleSize;
	Vec2 mOrigin;

	float m_x;
	float m_y;
	int m_hp; // ���� hp

	int mState;

	float jumpTick;
	bool isJump;
	const float jumpYpos = 2; // ���� y�� �ӵ�
	PLAYER_DIR mJumpDir; // ���� �� ��������Ʈ ����

	int mCollisionIdx;
	bool misCollision;
	bool misObstacleCollision;
	bool misTouch;
	bool isFlip;
	PLAYER_DIR mTouchDir; // ��ġ ����

	void onInit(); // �⺻ ���� �ʱ�ȭ
	void onLoadSprites(); // ��������Ʈ �ʱ�ȭ

	bool IsDamaged = false;

public:

	virtual bool init();

	CREATE_FUNC(Character);

	void onRelease();
	
	void onUpdate(float delta, Block** block, int sNum, int maxNum);
	void onFallingMyPosition(float delta); // y�� �ϰ� ó��
	void onMoveXPosition(float delta); // ���� �� x�� �̵� ó��

	void onJump(float delta, float blockspeed); // ���� ó��
	void onDieMove(); // ������ 0���� �� �״� ��� �Լ�

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