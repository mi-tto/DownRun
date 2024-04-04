#ifndef __dataSingleton__
#define __dataSingleton__

#include <iostream>

class dataSingleton
{
private:
	dataSingleton() {};
	static dataSingleton* m_pInstance;

public:
	static dataSingleton* getInstance();


	bool life = false;
	bool life2 = false;
	bool scroll = false;
	bool scroll2 = false;
	bool scrolldown = false;//5.19
	bool score = false;//5.19
	bool score2 = false;//5.19
	bool scoreup = false;//5.19
	bool buy = false;
	bool pop = false;
	bool stagechange = false;//5.25
	bool dust = false; //5.25
	bool dust2 = false;//5.25

	bool speed = false;//5.30
	bool speed2 = false;//5.30
	bool speeddown = false;//5.30
	int coin = 0;//5.30
};

#endif