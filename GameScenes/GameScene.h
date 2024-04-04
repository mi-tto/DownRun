#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

#include "Character.h"
#include "Block.h"
#include "Item.h"

#include "StageIdx.h"

USING_NS_CC;

#define HP_ONE				10
#define HP_TWO				20
#define HP_THREE			30

#define TAG_MIN		100
#define TAG_SEC		110
#define TAG_MIL		120

#define TAG_FIRST	130
#define TAG_SECOND  140
#define TAG_THIRD   150

#define TAG_SCORE 300

enum STAGE_NUM
{
	STAGE_1 = 1,
	STAGE_2,
	STAGE_3,
};

class GameScene : public cocos2d::Layer
{
private:

	static GameScene* s_ptr;
	
	Size mVisibleSize;
	Vec2 mOrigin;

	Character* mCharacter;
	Block** mBlock;
	Item* mItem;

	StageIdx* mLayer;

	const int startBlockNum = 0;
	const int blockMAX = 5;

	bool G_pause;
	bool check;

	bool isFirst;
	int mHpMinusNum;
	int mHpPlusNum;
	int mHpTagNum;
	bool isMinHp;

	int Min;
	int Sec;
	float Mil;
	int SecondMil;

	float Time;

	int AllScore;
	bool isStart;

	STAGE_NUM mCurState;
	bool isStageChange;

	bool restart;
	bool isdead;
	int second;

	int coin;

	GameScene(){}
public:

	virtual ~GameScene();
    static cocos2d::Scene* createScene();
	CREATE_FUNC(GameScene);

	static GameScene* Get_Instance()
	{
		if (s_ptr == NULL)
		{
			s_ptr = GameScene::create();
		}
		return s_ptr;
	}

	// √ ±‚»≠
    virtual bool init();
	void onGameDataInit();
	void onUiInit();

	void onLoadSprite();
	void onRelease();
	void onUpdate(float delta);
	void onChangeStageLayer();

	void pause(Ref *sender);

	StageIdx* GetStageLayer()
	{
		return mLayer;
	}

	void onDrawHp();
	void Score();
	void EndingScene();

	void scheduleCallBack(float delta);
	void scheduleCallBack2(float delta);
	void SetScore();
	
	void SetSec();
	void SetMin();
	void SetMil();
	void resetscore(float delta);//5.19
};

#endif // __HELLOWORLD_SCENE_H__