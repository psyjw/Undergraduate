#pragma once
#include "CW4Enemy.h"
class CW4Soldier :
	public CW4Enemy
{
public:
	CW4Soldier(CW4Engine* pEngine, int width, int height, int direction, int spawnTime);
	CW4Soldier(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int Pretime);
	~CW4Soldier();
	
	void DoUpdate(int iCurrentTime);
	int leftX = 1;
	int rightX = -1;
	
	
};

