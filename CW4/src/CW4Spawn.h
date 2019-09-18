#pragma once
#include "DisplayableObject.h"
#include "CW4JetFighter.h"
#include "CW4Soldier.h"
#include "CW4Tank.h"



class CW4Spawn :
	public DisplayableObject
{
public:
	CW4Spawn(CW4Engine* pEngine);
	CW4Spawn(CW4Engine* pEngine, int Timediff, int Pretime, int Enemynum, int Enemyindex);
	~CW4Spawn();
	void DoUpdate(int iCurrentTime);
	int timeDiff = 1000;
	int preTime = 0;
	int enemyNum = 0;
	int enemyIndex = 1;
	int enemyType;
	std::string save();
};

