#pragma once
#include "DisplayableObject.h"
#include "JPGImage.h"
#include "CW4Engine.h"
#include <string>

class CW4Enemy :
	public DisplayableObject
{
public:
	CW4Enemy(CW4Engine* pEngine, int width, int height, int direction, bool visible, int spawnTime);
	CW4Enemy(CW4Engine* pEngine, int iX, int iY, int direction, int Status, int Firerate, bool visible, int Enemytype, int preTime);
	~CW4Enemy();
	ImageData enemy[2], enemyResize;
	int side;
	void Draw();
	bool eliminate(int iX, int iY);
	void attack(int iX, int iY);
	
	
	CW4Engine* engine;
	int getY();
	int getX();
	int state = 0;
	int fireRate = 3000;
	int preTime = 0;
	int enemyType;
	char* score;
	std::string save();
};

