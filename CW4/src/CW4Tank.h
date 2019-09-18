#pragma once
#include "CW4Enemy.h"
class CW4Tank :
	public CW4Enemy
{
public:
	CW4Tank(CW4Engine* pEngine, int width, int height, int direction, int spawnTime);
	CW4Tank(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int Pretime);
	~CW4Tank();
	void DoUpdate(int iCurrentTime);
	int leftX = 1;
	int rightX = -1;
	
};

