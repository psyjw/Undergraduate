#pragma once
#include "CW4Enemy.h"
class CW4JetFighter :
	public CW4Enemy
{
public:
	CW4JetFighter(CW4Engine* pEngine, int width, int height, int direction, int spawnTime);
	CW4JetFighter(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int Pretime);
	~CW4JetFighter();
	void DoUpdate(int iCurrentTime);
	int scale = 1;
	int leftX = 1;
	int rightX = -1;
	
};

